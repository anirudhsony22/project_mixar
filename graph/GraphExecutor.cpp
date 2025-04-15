#include "GraphExecutor.hpp"
#include "../nodes/NodeFactory.hpp"
#include <unordered_set>
#include <functional>

void GraphExecutor::Evaluate(
    smkflow::Graph& graph,
    std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap
) {
    ShowAddNodePanel(graph, nodeMap);
    auto sortedNodes = TopologicalSort(graph, nodeMap);
    if (sortedNodes.empty()) {
        std::cerr << "[GraphExecutor] Evaluation aborted due to cycle." << std::endl;
        return;
    }

    for (auto* node : sortedNodes) {
        if (!nodeMap.count(node)) continue;

        BaseImageNode* current = nodeMap[node];

        // Gather all inputs
        std::vector<cv::Mat> inputs;

        bool hasValidInput = false;
        for (const auto& conn : graph.connections) {
            if (conn.toNodeId == node->name) {
                auto fromIt = graph.nodes.find(conn.fromNodeId);
                if (fromIt == graph.nodes.end()) {
                    std::cerr << "[Evaluate] Warning: fromNode " << conn.fromNodeId << " not found.\n";
                    continue;
                }
        
                auto* fromNode = fromIt->second.get();
                if (nodeMap.count(fromNode)) {
                    inputs.push_back(nodeMap[fromNode]->GetOutputImage(conn.fromSlot));
                    hasValidInput = true;
                }
            }
        }

        current->SetInputImages(inputs);
        current->Show(graph); // Renders node & computes output
    }
}


std::vector<smkflow::Node*> GraphExecutor::TopologicalSort(
    smkflow::Graph& graph,
    const std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap
) {
    std::unordered_map<smkflow::Node*, int> inDegree;
    std::unordered_map<smkflow::Node*, std::vector<smkflow::Node*>> adj;

    // Initialize
    for (const auto& [node, _] : nodeMap) {
        inDegree[node] = 0;
    }

    // Build graph edges
    for (const auto& conn : graph.connections) {
        auto fromIt = graph.nodes.find(conn.fromNodeId);
        auto toIt = graph.nodes.find(conn.toNodeId);
    
        if (fromIt == graph.nodes.end() || toIt == graph.nodes.end()) {
            std::cerr << "[TopologicalSort] Skipping invalid connection: "
                      << conn.fromNodeId << " → " << conn.toNodeId << std::endl;
            continue;
        }
    
        smkflow::Node* from = fromIt->second.get();
        smkflow::Node* to = toIt->second.get();
    
        if (nodeMap.count(from) && nodeMap.count(to)) {
            adj[from].push_back(to);
            inDegree[to]++;
        }
    }    

    // Queue for nodes with no incoming edges
    std::queue<smkflow::Node*> q;
    for (const auto& [node, deg] : inDegree) {
        if (deg == 0) q.push(node);
    }

    std::vector<smkflow::Node*> result;

    while (!q.empty()) {
        smkflow::Node* current = q.front(); q.pop();
        result.push_back(current);

        for (smkflow::Node* neighbor : adj[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Cycle check
    if (result.size() != nodeMap.size()) {
        std::cerr << "[GraphExecutor] Cycle detected in graph!" << std::endl;
        return {}; // Empty = failed
    }

    return result;
}


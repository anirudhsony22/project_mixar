#include "GraphExecutor.hpp"
#include <unordered_set>
#include <functional>

void GraphExecutor::Evaluate(
    smkflow::Graph& graph,
    std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap
) {
    std::unordered_set<smkflow::Node*> visited;

    std::function<void(smkflow::Node*)> visit = [&](smkflow::Node* node) {
        if (!node || visited.count(node)) return;
        visited.insert(node);

        for (auto* input : node->inputs) {
            visit(input);
        }

        if (nodeMap.count(node)) {
            BaseImageNode* current = nodeMap[node];
            // std::cout << "Rendering node: " << node->name << " @ " << current << std::endl;
        
            if (!node->inputs.empty()) {
                auto* upstream = node->inputs[0];
                if (nodeMap.count(upstream)) {
                    current->SetInputImage(nodeMap[upstream]->GetOutputImage());
                }
            }
        
            // std::cout << "Rendering node: " << node->name << std::endl;
            current->Show();
        }
    };

    for (const auto& [node, _] : nodeMap) {
        visit(node);
    }
}
#include "smkflow/Graph.hpp"
#include <imgui.h>
#include <iostream> // For std::cerr
#include "../../nodes/SlotUtils.hpp"

std::optional<std::pair<std::string, std::string>> connectionToRemove;

inline float ImLengthSqr(const ImVec2& v) {
    return v.x * v.x + v.y * v.y;
}

namespace smkflow {

void Graph::Show() {
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    float minDistSq = std::numeric_limits<float>::max();
    std::optional<std::pair<std::string, std::string>> nearestConnection;
    float influenceRadius = 15.0f;
    ImVec2 mousePos = ImGui::GetMousePos();

    std::optional<std::pair<std::string, std::string>> hoveredConnection;
    ImVec2 hoveredP1, hoveredP2;

    for (const auto& conn : connections) {
        auto fromIt = nodes.find(conn.fromNodeId);
        auto toIt = nodes.find(conn.toNodeId);
        if (fromIt == nodes.end() || toIt == nodes.end()) continue;

        Node* from = fromIt->second.get();
        Node* to = toIt->second.get();

        if (from->windowSize.x <= 0 || to->windowSize.x <= 0) continue;

        ImVec2 p1 = GetOutputSlotPos(*from, conn.fromSlot);
        ImVec2 p2 = GetInputSlotPos(*to, conn.toSlot);

        // === 1. Draw curve
        drawList->AddBezierCubic(
            p1, p1 + ImVec2(50, 0),
            p2 - ImVec2(50, 0), p2,
            IM_COL32(200, 200, 100, 255), 2.0f
        );

        // === 2. Draw arrowhead
        float arrowSize = 10.0f;
        ImVec2 pLeft  = p2 + ImVec2(-arrowSize, -arrowSize / 2);
        ImVec2 pRight = p2 + ImVec2(-arrowSize,  arrowSize / 2);
        drawList->AddTriangleFilled(p2, pLeft, pRight, IM_COL32(200, 200, 100, 255));

        // === 3. Sample the curve and find closest point to mouse
        for (float t = 0.0f; t <= 1.0f; t += 0.05f) {
            ImVec2 pt = ImBezierCubicCalc(
                p1, p1 + ImVec2(50, 0),
                p2 - ImVec2(50, 0), p2, t
            );
            ImVec2 diff = pt - mousePos;
            float distSq = diff.x * diff.x + diff.y * diff.y;

            if (distSq < minDistSq && distSq < influenceRadius * influenceRadius) {
                minDistSq = distSq;
                nearestConnection = std::make_pair(conn.fromNodeId, conn.toNodeId);
            
                hoveredConnection = nearestConnection;
                hoveredP1 = p1;
                hoveredP2 = p2;
            }            
        }
    }

    if (hoveredConnection.has_value()) {
        drawList->AddBezierCubic(
            hoveredP1, hoveredP1 + ImVec2(50, 0),
            hoveredP2 - ImVec2(50, 0), hoveredP2,
            IM_COL32(255, 255, 0, 200), 4.0f  // yellow glow, thicker
        );
    }    

    // === 4. Trigger popup after drawing all connections
    if (nearestConnection.has_value() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
        selectedConnection = nearestConnection;
        ImGui::OpenPopup("DeleteConnectionPopup");
        ImGui::SetNextWindowPos(mousePos);
    }

    // === 5. Render popup
    if (ImGui::BeginPopup("DeleteConnectionPopup")) {
        if (ImGui::MenuItem("Delete Connection") && selectedConnection.has_value()) {
            connectionToRemove = selectedConnection;
            selectedConnection.reset();
        }
        ImGui::EndPopup();
    }

    // === 6. Remove if queued
    if (connectionToRemove.has_value()) {
        removeConnection(connectionToRemove->first, connectionToRemove->second);
        connectionToRemove.reset();
    }
}


Node* smkflow::Graph::AddNode(const std::string& name) {
    auto node = std::make_shared<Node>(name);
    this->nodes[name] = node;
    return node.get();
}


void Graph::addConnection(const Connection& conn) {
    connections.push_back(conn);

    auto fromIt = nodes.find(conn.fromNodeId);
    auto toIt = nodes.find(conn.toNodeId);

    if (fromIt == nodes.end() || toIt == nodes.end()) {
        std::cerr << "[Graph] Invalid connection: node(s) not found.\n";
        std::cerr << "  from: " << conn.fromNodeId << ", to: " << conn.toNodeId << "\n";
        return;
    }

    Node* fromNode = fromIt->second.get();
    Node* toNode = toIt->second.get();

    fromNode->outputs.push_back(toNode);

    if (conn.toSlot >= toNode->inputs.size()) {
        toNode->inputs.resize(conn.toSlot + 1);
    }

    toNode->inputs[conn.toSlot] = fromNode;
}


void Graph::removeConnection(const std::string& fromNodeId, const std::string& toNodeId) {
    std::cout << "[removeConnection] from:"<< fromNodeId << " to:" << toNodeId << "\n";
    connections.erase(
        std::remove_if(connections.begin(), connections.end(),
            [&](const Connection& conn) {
                return conn.fromNodeId == fromNodeId && conn.toNodeId == toNodeId;
            }),
        connections.end()
    );

    auto fromIt = nodes.find(fromNodeId);
    if (fromIt != nodes.end()) {
        Node* fromNode = fromIt->second.get();
        fromNode->outputs.erase(
            std::remove_if(fromNode->outputs.begin(), fromNode->outputs.end(),
                [&](Node* outPtr) {
                    return outPtr && outPtr->name == toNodeId;
                }),
            fromNode->outputs.end()
        );
    }

    auto toIt = nodes.find(toNodeId);
    if (toIt != nodes.end()) {
        Node* toNode = toIt->second.get();
        // std::cout << "[removeConnection] to:"<< toNodeId << " from:" << fromNodeId << "\n";

        for (size_t slot = 0; slot < toNode->inputs.size(); ++slot) {
            if (toNode->inputs[slot] && toNode->inputs[slot]->name == fromNodeId) {
                std::cout << "[removeConnection1] Nulling input slot " << slot
                          << " in node " << toNodeId << " (was from " << fromNodeId << ")\n";
                toNode->inputs[slot] = nullptr;
            }
            Node* inputPtr = toNode->inputs[slot];
            if (inputPtr && inputPtr->name == fromNodeId) {
                std::cout << "[removeConnection2] Nulling input slot " << slot
                          << " in node " << toNodeId << " (was from " << fromNodeId << ")\n";

                toNode->inputs[slot] = nullptr;
            }
        }
    }
}


void Graph::removeConnectionForTarget(const std::string& toNodeId) {
    connections.erase(
        std::remove_if(connections.begin(), connections.end(),
            [&](const Connection& conn) {
                return conn.toNodeId == toNodeId;
            }),
        connections.end()
    );

    auto it = nodes.find(toNodeId);
    if (it != nodes.end()) {
        Node* toNode = it->second.get();
        for (auto& ptr : toNode->inputs) {
            if (ptr) ptr = nullptr;
        }
    }
}


void Graph::removeNode(const std::string& nodeId) {
    connections.erase(
        std::remove_if(connections.begin(), connections.end(),
            [&](const Connection& conn) {
                return conn.fromNodeId == nodeId || conn.toNodeId == nodeId;
            }),
        connections.end()
    );
}


void Graph::removeConnectionForTargetSlot(const std::string& toNodeId, int toSlot) {
    connections.erase(
        std::remove_if(connections.begin(), connections.end(),
            [&](const Connection& conn) {
                return conn.toNodeId == toNodeId && conn.toSlot == toSlot;
            }),
        connections.end()
    );

    auto toIt = nodes.find(toNodeId);
    if (toIt != nodes.end()) {
        Node* toNode = toIt->second.get();
        if (toSlot < toNode->inputs.size()) {
            toNode->inputs[toSlot] = nullptr;
        }
    }
}




void Theme_Default() {
    ImGui::StyleColorsDark();
}

}

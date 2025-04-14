#pragma once
#include <string>
#include <iostream>
#include "smkflow/Graph.hpp"

void DrawInputSlot(const std::string& currentNodeName, smkflow::Graph& graph);
void DrawOutputSlot(const std::string& currentNodeName, int slot);

inline void EnforceSingleInput(smkflow::Graph& graph, const std::string& toNodeId, const std::string& newFromNodeId) {
    // Remove all existing connections into toNodeId
    std::vector<smkflow::Connection> toRemove;
    for (const auto& conn : graph.connections) {
        if (conn.toNodeId == toNodeId) {
            toRemove.push_back(conn);
        }
    }

    for (const auto& conn : toRemove) {
        std::cout << "[Graph] Removing old connection: " << conn.fromNodeId << " → " << conn.toNodeId << std::endl;
        graph.removeConnection(conn.fromNodeId, conn.toNodeId);
    }

    // Add the new connection
    std::cout << "[Graph] Connecting: " << newFromNodeId << " → " << toNodeId << std::endl;
    graph.addConnection({newFromNodeId, 0, toNodeId, 0});
}


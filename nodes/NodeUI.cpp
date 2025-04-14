#include "NodeUI.hpp"
#include <imgui.h>
#include <iostream>

void DrawInputSlot(const std::string& currentNodeId, smkflow::Graph& graph) {
    ImGui::Text("Input Slot:");
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_OUTPUT")) {
            std::string fromNodeId((const char*)payload->Data);

            // Check if this node already has an input
            bool alreadyConnected = false;
            for (const auto& conn : graph.connections) {
                if (conn.toNodeId == currentNodeId) {
                    alreadyConnected = true;
                    break;
                }
            }

            if (alreadyConnected) {
                std::cout << "[Connect] Node '" << currentNodeId
                          << "' already has an input. Rejecting new connection from '" 
                          << fromNodeId << "'\n";
                // Optional: show UI warning
                ImGui::OpenPopup("ConnectionWarning");
            } else {
                graph.addConnection({fromNodeId, 0, currentNodeId, 0});
                std::cout << "[Connect] " << fromNodeId << " → " << currentNodeId << std::endl;
            }
        }
        ImGui::EndDragDropTarget();
    }

    // Optional: Popup warning UI
    if (ImGui::BeginPopup("ConnectionWarning")) {
        ImGui::Text("This node only accepts one input.");
        if (ImGui::Button("OK")) ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}


void DrawOutputSlot(const std::string& currentNodeName) {
    ImGui::Text("Output Slot:");
    if (ImGui::Button(("Send##" + currentNodeName).c_str())) {}

    if (ImGui::BeginDragDropSource()) {
        ImGui::SetDragDropPayload("NODE_OUTPUT", currentNodeName.c_str(), currentNodeName.length() + 1);
        ImGui::Text("Dragging: %s", currentNodeName.c_str());
        ImGui::EndDragDropSource();
    }
}
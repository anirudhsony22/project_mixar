#include "NodeUI.hpp"
#include <imgui.h>
#include <iostream>

void DrawInputSlot(const std::string& currentNodeName, smkflow::Graph& graph) {
    ImGui::Text("Input Slot:");

    // Right-click menu
    if (ImGui::BeginPopupContextItem(("##input_slot_" + currentNodeName).c_str())) {
        // Check if this node has an input connection
        for (const auto& conn : graph.connections) {
            if (conn.toNodeId == currentNodeName) {
                if (ImGui::MenuItem(("Disconnect from " + conn.fromNodeId).c_str())) {

                    // Remove connection
                    graph.removeConnection(conn.fromNodeId, conn.toNodeId);
                    break;
                }
            }
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_OUTPUT")) {
            std::string fromNodeId((const char*)payload->Data);

            graph.addConnection({fromNodeId, 0, currentNodeName, 0});
        }
        ImGui::EndDragDropTarget();
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
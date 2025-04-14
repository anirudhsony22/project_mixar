#include "NodeUI.hpp"
#include <imgui.h>
#include <iostream>

static std::string pendingFromNode;
static std::string pendingToNode;
static bool showReplaceDialog = false;

void DrawInputSlot(const std::string& currentNodeId, smkflow::Graph& graph) {
    ImGui::Text("Input Slot:");
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_OUTPUT")) {
            std::string fromNodeId((const char*)payload->Data);

            bool alreadyConnected = false;
            for (const auto& conn : graph.connections) {
                if (conn.toNodeId == currentNodeId) {
                    alreadyConnected = true;
                    break;
                }
            }

            if (alreadyConnected) {
                // Store temp and trigger popup
                pendingFromNode = fromNodeId;
                pendingToNode = currentNodeId;
                showReplaceDialog = true;
                ImGui::OpenPopup("Replace Connection?");
            } else {
                graph.addConnection({fromNodeId, 0, currentNodeId, 0});
                std::cout << "[Connect] " << fromNodeId << " → " << currentNodeId << std::endl;
            }
        }
        ImGui::EndDragDropTarget();
    }

    // Optional: Popup warning UI
    if (ImGui::BeginPopupModal("Replace Connection?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("This node already has an input.\nReplace existing connection?");
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(100, 0))) {
            graph.removeConnectionForTarget(pendingToNode);
            graph.addConnection({pendingFromNode, 0, pendingToNode, 0});
            showReplaceDialog = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(100, 0))) {
            showReplaceDialog = false;
            ImGui::CloseCurrentPopup();
        }
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
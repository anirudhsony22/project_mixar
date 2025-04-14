#include "NodeUI.hpp"
#include <imgui.h>
#include <iostream>

static std::string pendingFromNode;
static std::string pendingToNode;
static int pendingFromSlot = 0;
static bool showReplaceDialog = false;

void DrawInputSlot(const std::string& currentNodeId, smkflow::Graph& graph) {
    ImGui::Text("Input Slot:");

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_OUTPUT")) {
            std::string data((const char*)payload->Data);
            auto delim = data.find("::");

            std::string fromNodeId = data.substr(0, delim);
            int fromSlot = std::stoi(data.substr(delim + 2)); 

            if (delim != std::string::npos) {
                fromNodeId = data.substr(0, delim);
                fromSlot = std::stoi(data.substr(delim + 2));
            }

            bool alreadyConnected = false;
            for (const auto& conn : graph.connections) {
                if (conn.toNodeId == currentNodeId) {
                    alreadyConnected = true;
                    break;
                }
            }

            if (alreadyConnected) {
                pendingFromNode = fromNodeId;
                pendingFromSlot = fromSlot;
                pendingToNode = currentNodeId;
                showReplaceDialog = true;
                ImGui::OpenPopup("Replace Connection?");
            } else {
                graph.addConnection({fromNodeId, fromSlot, currentNodeId, 0});
                std::cout << "[Connect] " << fromNodeId << " [slot " << fromSlot << "] → " << currentNodeId << std::endl;
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (ImGui::BeginPopupModal("Replace Connection?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("This node already has an input.\nReplace existing connection?");
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(100, 0))) {
            graph.removeConnectionForTarget(pendingToNode);
            graph.addConnection({pendingFromNode, pendingFromSlot, pendingToNode, 0});
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

void DrawOutputSlot(const std::string& nodeId, int slot = 0) {
    ImGui::Button(("Output##" + nodeId + std::to_string(slot)).c_str());
    if (ImGui::BeginDragDropSource()) {
        std::string payload = nodeId + "::" + std::to_string(slot);
        ImGui::SetDragDropPayload("NODE_OUTPUT", payload.c_str(), payload.size() + 1);
        ImGui::Text("Drag: %s [slot %d]", nodeId.c_str(), slot);
        ImGui::EndDragDropSource();
    }
}
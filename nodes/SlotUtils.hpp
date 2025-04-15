#pragma once
#include <imgui.h>
#include <string>
#include "smkflow/Graph.hpp"  // for smkflow::Node

inline ImVec2 GetInputSlotPos(const smkflow::Node& node, int index) {
    return node.windowPos + ImVec2(0, 35 + index * 30);
}


inline ImVec2 GetOutputSlotPos(const smkflow::Node& node, int index) {
    return node.windowPos + ImVec2(node.windowSize.x, 35 + index * 30);
}


inline void DrawInputPort(smkflow::Node& node, int index, smkflow::Graph& graph) {
    ImVec2 portPos = GetInputSlotPos(node, index);
    ImDrawList* draw = ImGui::GetWindowDrawList();

    draw->AddCircleFilled(portPos, 10.0f, IM_COL32(100, 200, 255, 255));  // blue

    ImVec2 dropSize(30, 30);
    ImGui::SetCursorScreenPos(portPos - dropSize * 0.5f);
    ImGui::InvisibleButton(("##input_drop_" + std::to_string(index)).c_str(), dropSize);

    if (ImGui::IsItemHovered()) {
        draw->AddCircle(portPos, 9.0f, IM_COL32(255, 255, 0, 255), 16, 2.0f);
    }

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_OUTPUT")) {
            std::string data((const char*)payload->Data);
            auto delim = data.find("::");
            std::string fromNode = data.substr(0, delim);
            int fromSlot = std::stoi(data.substr(delim + 2));

            // 🔍 Check if this input slot is already connected
            bool alreadyConnected = false;
            for (const auto& conn : graph.connections) {
                if (conn.toNodeId == node.name && conn.toSlot == index) {
                    alreadyConnected = true;
                    break;
                }
            }

            if (alreadyConnected) {
                // Replace connection without dialog for now
                graph.removeConnectionForTargetSlot(node.name, index);
            }

            graph.addConnection({fromNode, fromSlot, node.name, index});
            std::cout << "[Connect] " << fromNode << " → " << node.name << " [slot " << index << "]" << std::endl;
        }
        ImGui::EndDragDropTarget();
    }
}


inline void DrawOutputPort(const smkflow::Node& node, int index) {
    ImVec2 portPos = GetOutputSlotPos(node, index);
    ImDrawList* draw = ImGui::GetWindowDrawList();

    draw->AddCircleFilled(portPos, 10.0f, IM_COL32(255, 150, 150, 255));  // red

    ImGui::SetCursorScreenPos(portPos - ImVec2(10, 10));
    ImGui::InvisibleButton(("##output_drag_" + std::to_string(index)).c_str(), ImVec2(20, 20));

    if (ImGui::BeginDragDropSource()) {
        std::string payload = node.name + "::" + std::to_string(index);
        ImGui::SetDragDropPayload("NODE_OUTPUT", payload.c_str(), payload.size() + 1);
        ImGui::Text("Drag from %s [slot %d]", node.name.c_str(), index);
        ImGui::EndDragDropSource();
    }
}

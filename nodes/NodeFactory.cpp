#include "NodeFactory.hpp"
#include "ImageInputNode.hpp"
#include "BlurNode.hpp"
#include "BrightnessContrastNode.hpp"
#include "ColorSplitNode.hpp"
#include "OutputNode.hpp"
#include "ThresholdNode.hpp"
#include "EdgeDetectionNode.hpp"
#include "BlendNode.hpp"


const float baseY = 50.0f;
const float ySpacing = 150.0f;

const float inputX = 100.0f;
const float blurX = 300.0f;
const float bcX = 500.0f;
const float outputX = 700.0f;

void ShowAddNodePanel(
    smkflow::Graph& graph,
    std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap
) {
    static int inputCount = 1;
    static int blurCount = 1;
    static int bcCount = 1;
    static int outputCount = 1;
    static int csCount = 1;
    static int thresholdCount = 1;
    static int edgeCount = 1;
    static int blendCount = 1;



    ImGui::Begin("Add Nodes");

    if (ImGui::Button("Add Image Input")) {
        std::string name = "input" + std::to_string(inputCount++);
        auto input = std::make_shared<ImageInputNode>(name);
        input->position = ImVec2(inputX, baseY + (inputCount - 1) * ySpacing); // 👈 stack vertically
        graph.nodes[name] = input;
        nodeMap[input.get()] = input.get();
    }

    if (ImGui::Button("Add Blur")) {
        std::string name = "blur" + std::to_string(blurCount++);
        auto blur = std::make_shared<BlurNode>(name);
        blur->position = ImVec2(blurX, baseY + (blurCount - 1) * ySpacing);
        graph.nodes[name] = blur;
        nodeMap[blur.get()] = blur.get();
    }

    if (ImGui::Button("Add Brightness/Contrast")) {
        std::string name = "brightness" + std::to_string(bcCount++);
        auto bc = std::make_shared<BrightnessContrastNode>(name);
        bc->position = ImVec2(bcX, baseY + (bcCount - 1) * ySpacing);
        graph.nodes[name] = bc;
        nodeMap[bc.get()] = bc.get();
    }

    if (ImGui::Button("Add Output")) {
        std::string name = "output" + std::to_string(outputCount++);
        auto output = std::make_shared<OutputNode>(name);
        output->position = ImVec2(outputX, baseY + (outputCount - 1) * ySpacing);
        graph.nodes[name] = output;
        nodeMap[output.get()] = output.get();
    }

    if (ImGui::Button("Add Color Split Node")) {
        std::string name = "colorsplit" + std::to_string(csCount++);
        auto cs = std::make_shared<ColorSplitNode>(name);
        cs->position = ImVec2(300, baseY + (csCount - 1) * ySpacing);
        graph.nodes[name] = cs;
        nodeMap[cs.get()] = cs.get();
    }    

    if (ImGui::Button("Add Threshold Node")) {
        std::string name = "threshold" + std::to_string(thresholdCount++);
        auto node = std::make_shared<ThresholdNode>(name);
        node->position = ImVec2(600, baseY + (thresholdCount - 1) * ySpacing);
        graph.nodes[name] = node;
        nodeMap[node.get()] = node.get();
    }

    if (ImGui::Button("Add Edge Detection Node")) {
        std::string name = "edge" + std::to_string(edgeCount++);
        auto node = std::make_shared<EdgeDetectionNode>(name);
        node->position = ImVec2(600, baseY + (edgeCount - 1) * ySpacing);
        graph.nodes[name] = node;
        nodeMap[node.get()] = node.get();
    }

    if (ImGui::Button("Add Blend Node")) {
        std::string name = "blend" + std::to_string(blendCount++);
        auto node = std::make_shared<BlendNode>(name);
        node->position = ImVec2(800, baseY + (blendCount - 1) * ySpacing);
        graph.nodes[name] = node;
        nodeMap[node.get()] = node.get();
    }

    ImGui::End();
}

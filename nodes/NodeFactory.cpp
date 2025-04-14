#include "NodeFactory.hpp"
#include "ImageInputNode.hpp"
#include "BlurNode.hpp"
#include "BrightnessContrastNode.hpp"
#include "ColorSplitNode.hpp"
#include "ColorSplitNode.hpp"
#include "OutputNode.hpp"

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

    ImGui::End();
}

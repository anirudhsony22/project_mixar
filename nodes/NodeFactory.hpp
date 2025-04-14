#pragma once

#include <string>
#include <memory>
#include <imgui.h>
#include <unordered_map>

#include "smkflow/Graph.hpp"
#include "BaseImageNode.hpp"

// Forward declarations
class ImageInputNode;
class BlurNode;
class BrightnessContrastNode;
class OutputNode;

void ShowAddNodePanel(
    smkflow::Graph& graph,
    std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap
);

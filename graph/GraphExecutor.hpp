#pragma once
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "smkflow/Graph.hpp"
#include "../nodes/BaseImageNode.hpp"

class GraphExecutor {
public:
    void Evaluate(smkflow::Graph& graph,
                  std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap);
};
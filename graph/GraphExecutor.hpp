#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include "smkflow/Graph.hpp"
#include "../nodes/BaseImageNode.hpp"

class GraphExecutor {
public:
    // Main entry point
    void Evaluate(smkflow::Graph& graph,
                  std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap);

private:
    // Returns nodes in topological order (empty if cycle)
    std::vector<smkflow::Node*> TopologicalSort(
        smkflow::Graph& graph,
        const std::unordered_map<smkflow::Node*, BaseImageNode*>& nodeMap);

    // Map to hold the outputs of each node (intermediate results)
    std::unordered_map<smkflow::Node*, cv::Mat> outputCache;
};

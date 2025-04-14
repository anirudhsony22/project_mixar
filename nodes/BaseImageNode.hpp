#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace smkflow {
    class Graph;
}

class BaseImageNode {
public:
    virtual ~BaseImageNode() = default;

    // Receives input images from connected upstream nodes
    virtual void SetInputImages(const std::vector<cv::Mat>& images) = 0;

    // Returns the processed output image
    virtual const cv::Mat& GetOutputImage(int slot = 0) const = 0;

    // Renders the ImGui interface and processes image if needed
    virtual void Show(smkflow::Graph& graph) = 0;
};
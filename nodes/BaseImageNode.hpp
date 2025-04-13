#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class BaseImageNode {
public:
    virtual ~BaseImageNode() = default;

    // Receives input images from connected upstream nodes
    virtual void SetInputImages(const std::vector<cv::Mat>& images) = 0;

    // Returns the processed output image
    virtual const cv::Mat& GetOutputImage() const = 0;

    // Renders the ImGui interface and processes image if needed
    virtual void Show() = 0;
};
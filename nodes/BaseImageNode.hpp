#pragma once
#include <opencv2/opencv.hpp>

class BaseImageNode {
public:
    virtual ~BaseImageNode() = default;

    virtual void SetInputImage(const cv::Mat& input) = 0;
    virtual const cv::Mat& GetOutputImage() const = 0;

    // Optional: UI render method if needed
    virtual void Show() = 0;
};

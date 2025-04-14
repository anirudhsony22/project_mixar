#pragma once
#include <opencv2/opencv.hpp>

inline cv::Mat EnsureRGB(const cv::Mat& img) {
    cv::Mat rgb;

    if (img.empty()) {
        return rgb;  // Return empty safely
    }

    switch (img.channels()) {
        case 1:
            cv::cvtColor(img, rgb, cv::COLOR_GRAY2RGB);
            break;
        case 3:
            rgb = img.clone();
            break;
        case 4:
            cv::cvtColor(img, rgb, cv::COLOR_RGBA2RGB);
            break;
        default:
            std::cerr << "[EnsureRGB] Unsupported channel count: " << img.channels() << "\n";
            break;
    }

    return rgb;
}
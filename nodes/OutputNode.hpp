// OutputNode.hpp
#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"

class OutputNode : public BaseImageNode {
public:
    OutputNode();
    void SetInputImage(const cv::Mat& input) override;
    const cv::Mat& GetOutputImage() const override;
    void Show() override;

private:
    cv::Mat image;
    GLuint textureID = 0;
    bool hasImage = false;
    std::string format = "png";

    void CreateGLTexture();
    void CleanupTexture();
    void SaveImage();
};
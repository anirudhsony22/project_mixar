// BlurNode.hpp
#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"

class BlurNode : public BaseImageNode {
public:
    BlurNode();

    void SetInputImage(const cv::Mat& input) override;
    const cv::Mat& GetOutputImage() const override;
    void Show() override;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;

    int blurRadius = 3;
    bool hasInput = false;
    bool needsUpdate = true;

    GLuint textureID = 0;

    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
};
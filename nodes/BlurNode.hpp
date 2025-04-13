#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h>

#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"  // For smkflow::Node

class BlurNode : public smkflow::Node, public BaseImageNode {
public:
    BlurNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
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

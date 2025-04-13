#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h>

#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"  // For smkflow::Node

class ImageInputNode : public smkflow::Node, public BaseImageNode {
public:
    ImageInputNode(const std::string& name);

    // BaseImageNode overrides
    void SetInputImages(const std::vector<cv::Mat>& images) override;
    void Show() override;
    const cv::Mat& GetOutputImage() const override;

private:
    cv::Mat image;
    std::string filename;
    int width = 0;
    int height = 0;
    bool hasImage = false;

    GLuint textureID = 0;

    void LoadImage(const std::string& path);
    void CreateGLTexture();
    void CleanupTexture();
};

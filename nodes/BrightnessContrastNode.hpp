// BrightnessContrastNode.hpp
#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h> // For GLuint on macOS

#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class BrightnessContrastNode : public smkflow::Node, public BaseImageNode {
public:
    BrightnessContrastNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
    void Show(smkflow::Graph& graph) override;
    const cv::Mat& GetOutputImage(int slot) const override;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    bool hasInput = false;
    bool needsUpdate = true;

    float brightness = 0.0f;   // range: -100 to +100
    float contrast = 1.0f;     // range: 0.0 to 3.0

    GLuint textureID = 0;

    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
};
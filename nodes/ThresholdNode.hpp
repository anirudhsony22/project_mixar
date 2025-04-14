#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class ThresholdNode : public smkflow::Node, public BaseImageNode {
public:
    ThresholdNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
    const cv::Mat& GetOutputImage(int slot = 0) const override;
    void Show(smkflow::Graph& graph) override;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    bool hasInput = false;
    bool needsUpdate = true;

    int thresholdValue = 127;
    int maxValue = 255;
    int method = 0; // 0=Binary, 1=Adaptive Mean, 2=Adaptive Gaussian, 3=Otsu

    GLuint textureID = 0;

    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
};

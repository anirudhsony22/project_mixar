#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class BlendNode : public smkflow::Node, public BaseImageNode {
public:
    BlendNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
    const cv::Mat& GetOutputImage(int slot = 0) const override;
    void Show(smkflow::Graph& graph) override;

private:
    std::vector<cv::Mat> inputImages;
    cv::Mat outputImage;
    bool hasInput = false;
    bool needsUpdate = true;

    int blendMode = 0; // 0 = Normal, 1 = Multiply, 2 = Screen, 3 = Overlay, 4 = Difference
    float blendFactor = 0.5f;

    GLuint textureID = 0;

    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
};

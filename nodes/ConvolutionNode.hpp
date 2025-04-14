#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class ConvolutionNode : public smkflow::Node, public BaseImageNode {
public:
    ConvolutionNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
    const cv::Mat& GetOutputImage(int slot = 0) const override;
    void Show(smkflow::Graph& graph) override;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    bool hasInput = false;
    bool needsUpdate = true;

    bool use5x5 = false;
    float kernel5x5[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    float kernel3x3[3][3] = {
        { 0, -1,  0 },
        { -1, 5, -1 },
        { 0, -1,  0 }
    };
    int selectedPreset = 0;
    bool normalize = false;

    GLuint textureID = 0;

    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
    void ApplyPreset(int presetIndex);
};

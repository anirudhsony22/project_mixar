#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class ColorSplitNode : public smkflow::Node, public BaseImageNode {
public:
    ColorSplitNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
    const cv::Mat& GetOutputImage(int slot) const override;
    void Show(smkflow::Graph& graph) override;

private:
    cv::Mat inputImage;
    cv::Mat channelR, channelG, channelB;
    cv::Mat outputImage; // not used directly but required
    bool hasInput = false;
    bool needsUpdate = true;

    GLuint texR = 0, texG = 0, texB = 0;

    void UpdateImages();
    void CreateGLTexture(GLuint& texID, const cv::Mat& channel, char tint);
    void CleanupTextures();
};

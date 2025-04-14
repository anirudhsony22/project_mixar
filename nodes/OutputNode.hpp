#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h>

#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class OutputNode : public smkflow::Node, public BaseImageNode {
public:
    OutputNode(const std::string& name);
    void SetInputImages(const std::vector<cv::Mat>& images) override;
    void Show(smkflow::Graph& graph) override;
    const cv::Mat& GetOutputImage(int slot = 0) const override;

private:
    cv::Mat inputImage;
    GLuint textureID = 0;
    bool hasInput = false;
    bool needsUpdate = true;

    std::string outputPath;
    
    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
    void SaveImage();
};

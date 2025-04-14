#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class NoiseNode : public smkflow::Node, public BaseImageNode {
public:
    NoiseNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>&) override {}
    const cv::Mat& GetOutputImage(int slot = 0) const override;
    void Show(smkflow::Graph& graph) override;

private:
    cv::Mat outputImage;
    bool needsUpdate = true;

    int noiseType = 0;      // 0 = white noise, 1 = checkerboard
    int width = 256;
    int height = 256;
    int gridSize = 32;      // checkerboard grid size
    int seed = 42;

    GLuint textureID = 0;

    void GenerateNoise();
    void CreateGLTexture();
    void CleanupTexture();
};

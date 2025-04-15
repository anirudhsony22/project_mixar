#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"
#include "FastNoiseLite.h"

enum NoiseMode { WHITE = 0, CHECKERBOARD, PERLIN, SIMPLEX, WORLEY };

class NoiseNode : public smkflow::Node, public BaseImageNode {
public:
    NoiseNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images);
    const cv::Mat& GetOutputImage(int slot = 0) const override;
    void Show(smkflow::Graph& graph) override;

private:
    cv::Mat outputImage;
    cv::Mat displacementSource; // optional input for warping
    float displacementStrength = 20.0f;

    bool needsUpdate = true;

    int noiseType = 0;      // 0 = white noise, 1 = checkerboard
    int width = 256;
    int height = 256;
    int gridSize = 32;      // checkerboard grid size
    int seed = 42;
    float scale = 0.05f;
    int octaves = 4;
    float persistence = 0.5f;
    bool displaceOutput = false;

    FastNoiseLite fn;

    GLuint textureID = 0;

    void GenerateNoise();
    void CreateGLTexture();
    void CleanupTexture();
};

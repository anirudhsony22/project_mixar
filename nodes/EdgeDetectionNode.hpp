#pragma once
#include <opencv2/opencv.hpp>
#include <imgui.h>
#include <OpenGL/gl3.h>
#include "BaseImageNode.hpp"
#include "smkflow/Graph.hpp"

class EdgeDetectionNode : public smkflow::Node, public BaseImageNode {
public:
    EdgeDetectionNode(const std::string& name);

    void SetInputImages(const std::vector<cv::Mat>& images) override;
    const cv::Mat& GetOutputImage(int slot = 0) const override;
    void Show(smkflow::Graph& graph) override;

private:
    cv::Mat inputImage;
    cv::Mat outputImage;
    bool hasInput = false;
    bool needsUpdate = true;

    int method = 0; // 0 = Sobel, 1 = Canny

    // Sobel settings
    int sobelDx = 1;
    int sobelDy = 1;
    int sobelKernel = 3;

    // Canny settings
    int cannyThreshold1 = 50;
    int cannyThreshold2 = 150;

    GLuint textureID = 0;

    void UpdateImage();
    void CreateGLTexture();
    void CleanupTexture();
};

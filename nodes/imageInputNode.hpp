#pragma once
// #include <GL/gl.h>
#include <OpenGL/gl3.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include "BaseImageNode.hpp"

class ImageInputNode : public BaseImageNode {
public:
    ImageInputNode() noexcept;
    void SetInputImage(const cv::Mat& input) override;
    const cv::Mat& GetOutputImage() const override;
    void Show() override;

private:
    cv::Mat image;
    GLuint textureID = 0;
    int width = 0, height = 0;
    std::string filename;
    bool hasImage = false;

    void LoadImage(const std::string& path);
    void CreateGLTexture();
    void CleanupTexture();
};

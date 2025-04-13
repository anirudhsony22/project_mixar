// BrightnessContrastNode.hpp
#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>
#include <OpenGL/gl3.h> // For GLuint on macOS
#include "BaseImageNode.hpp"

class BrightnessContrastNode  : public BaseImageNode {
public:
    BrightnessContrastNode();
    void SetInputImage(const cv::Mat& input);
    void Show();
    const cv::Mat& GetOutputImage() const;

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
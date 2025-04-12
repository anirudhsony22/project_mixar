#pragma once
// #include <GL/gl.h>
#include <OpenGL/gl3.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <imgui.h>

class ImageInputNode {
public:
    ImageInputNode();
    void Show();
    const cv::Mat& GetImage() const;

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

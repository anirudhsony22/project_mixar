#define GL_SILENCE_DEPRECATION
#include "ImageInputNode.hpp"
#include <opencv2/imgcodecs.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

ImageInputNode::ImageInputNode() noexcept {}

void ImageInputNode::SetInputImage(const cv::Mat& input) {
    static char filepath[512] = "/Users/anirudhsony/Downloads/Untitled.PNG";  // Buffer to hold user path

    ImGui::InputText("Image Path", filepath, IM_ARRAYSIZE(filepath));

    if (ImGui::Button("Load Image")) {
        LoadImage(filepath);
    }

    if (hasImage) {
        ImGui::Text("Loaded: %s", filename.c_str());
        ImGui::Text("%dx%d", width, height);
        ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
    } else {
        ImGui::Text("No image loaded");
    }
}

void ImageInputNode::LoadImage(const std::string& path) {
    cv::Mat img = cv::imread(path);
    if (img.empty()) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return;
    }
    std::cout<<img.channels()<<std::endl;
    if (img.channels() == 4) {
        cv::cvtColor(img, image, cv::COLOR_BGRA2RGBA);
    } else {
        cv::cvtColor(img, image, cv::COLOR_BGR2RGB);
    }    
    cv::cvtColor(img, image, cv::COLOR_BGR2RGB);
    width = image.cols;
    height = image.rows;
    filename = path;
    hasImage = true;
    CreateGLTexture();
}

void ImageInputNode::CreateGLTexture() {
    CleanupTexture();
    GLenum format = (image.channels() == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.cols, image.rows, 0, format, GL_UNSIGNED_BYTE, image.data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageInputNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

void ImageInputNode::Show() {
    if (ImGui::Begin("Image Input")) {
        static char filepath[512] = "test.jpg";
        ImGui::InputText("Path", filepath, IM_ARRAYSIZE(filepath));

        if (ImGui::Button("Load")) {
            LoadImage(filepath);
        }

        if (hasImage) {
            ImGui::Text("%dx%d", width, height);
            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        }
    }
    ImGui::End();
}

const cv::Mat& ImageInputNode::GetOutputImage() const {
    return image;
}

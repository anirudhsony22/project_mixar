#include "imageInputNode.hpp"
#include <opencv2/imgcodecs.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

ImageInputNode::ImageInputNode() {}

void ImageInputNode::Show() {
    ImGui::Begin("Image Input Node");

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

    ImGui::End();
}

void ImageInputNode::LoadImage(const std::string& path) {
    cv::Mat img = cv::imread(path);
    if (img.empty()) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return;
    }
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
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageInputNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

const cv::Mat& ImageInputNode::GetImage() const {
    return image;
}

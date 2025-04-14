#define GL_SILENCE_DEPRECATION
#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <GLFW/glfw3.h>

#include "ImageInputNode.hpp"
#include "NodeUI.hpp"

ImageInputNode::ImageInputNode(const std::string& name)
    : smkflow::Node(name) {}

void ImageInputNode::SetInputImages(const std::vector<cv::Mat>&) {
    // Input nodes do not receive upstream images — do nothing.
}

void ImageInputNode::Show(smkflow::Graph& graph) {
    if (ImGui::Begin(("Image Input: " + name).c_str())) {
        ImGui::InputText("Path", filepath, IM_ARRAYSIZE(filepath));

        if (ImGui::Button("Load")) {
            LoadImage(filepath);
        }

        if (hasImage) {
            ImGui::Text("File: %s", filename.c_str());
            ImGui::Text("Dimensions: %d x %d", width, height);
            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        } else {
            ImGui::Text("No image loaded.");
        }

        DrawOutputSlot(name, 0); // optional
    }
    ImGui::End();
}

void ImageInputNode::LoadImage(const std::string& path) {
    cv::Mat img = cv::imread(path);
    if (img.empty()) {
        std::cerr << "[ImageInputNode] Failed to load image: " << path << std::endl;
        return;
    }

    // Ensure image is RGB (3-channel) or RGBA (4-channel)
    if (img.channels() == 4) {
        cv::cvtColor(img, image, cv::COLOR_BGRA2RGBA);
    } else {
        cv::cvtColor(img, image, cv::COLOR_BGR2RGB);
    }

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

const cv::Mat& ImageInputNode::GetOutputImage(int slot) const {
    return image;
}
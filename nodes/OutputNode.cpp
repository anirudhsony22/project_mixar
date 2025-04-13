#define GL_SILENCE_DEPRECATION
#include "OutputNode.hpp"
#include <opencv2/imgcodecs.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

OutputNode::OutputNode(const std::string& name)
    : smkflow::Node(name) {}

void OutputNode::SetInputImages(const std::vector<cv::Mat>& images) {
    if (images.empty() || images[0].empty()) return;
    images[0].copyTo(inputImage);
    hasInput = true;
    needsUpdate = true;
}

void OutputNode::Show() {
    if (ImGui::Begin("Output Node")) {
        if (hasInput) {
            if (needsUpdate) UpdateImage();

            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));

            static char buffer[256] = "output.png";
            ImGui::InputText("Filename", buffer, IM_ARRAYSIZE(buffer));

            if (ImGui::Button("Save Image")) {
                outputPath = buffer;
                SaveImage();
            }
        } else {
            ImGui::Text("No input image.");
        }
    }
    ImGui::End();
}

void OutputNode::UpdateImage() {
    CreateGLTexture();
    needsUpdate = false;
}

const cv::Mat& OutputNode::GetOutputImage() const {
    return inputImage;
}

void OutputNode::CreateGLTexture() {
    CleanupTexture();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = inputImage.channels() == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, inputImage.cols, inputImage.rows, 0,
                 format, GL_UNSIGNED_BYTE, inputImage.data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OutputNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

void OutputNode::SaveImage() {
    if (!inputImage.empty() && !outputPath.empty()) {
        if (!cv::imwrite(outputPath, inputImage)) {
            std::cerr << "[OutputNode] Failed to save image to " << outputPath << std::endl;
        } else {
            std::cout << "[OutputNode] Saved image to " << outputPath << std::endl;
        }
    }
}
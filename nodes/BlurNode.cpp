#include "BlurNode.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>

BlurNode::BlurNode() {}

void BlurNode::SetInputImage(const cv::Mat& input) {
    if (input.empty()) return;
    input.copyTo(inputImage);
    hasInput = true;
    needsUpdate = true;
}

void BlurNode::Show() {
    if (ImGui::Begin("Blur Node")) {
        if (hasInput) {
            ImGui::SliderInt("Radius", &blurRadius, 1, 20);

            // Keep radius odd for Gaussian blur
            if (blurRadius % 2 == 0) blurRadius += 1;

            if (ImGui::Button("Update") || ImGui::IsItemDeactivatedAfterEdit()) {
                needsUpdate = true;
            }

            if (needsUpdate) {
                UpdateImage();
            }

            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        } else {
            ImGui::Text("No input image.");
        }
    }
    ImGui::End();
}

void BlurNode::UpdateImage() {
    if (!hasInput) return;

    cv::GaussianBlur(inputImage, outputImage, cv::Size(blurRadius, blurRadius), 0);
    CreateGLTexture();
    needsUpdate = false;
}

const cv::Mat& BlurNode::GetOutputImage() const {
    return outputImage;
}

void BlurNode::CreateGLTexture() {
    CleanupTexture();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = outputImage.channels() == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, outputImage.cols, outputImage.rows, 0,
                 format, GL_UNSIGNED_BYTE, outputImage.data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void BlurNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

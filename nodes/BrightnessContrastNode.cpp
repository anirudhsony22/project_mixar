#include "BrightnessContrastNode.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>

BrightnessContrastNode::BrightnessContrastNode() {}

void BrightnessContrastNode::SetInputImage(const cv::Mat& input) {
    if (input.empty()) return;
    input.copyTo(inputImage);
    hasInput = true;
    needsUpdate = true;
}

void BrightnessContrastNode::Show() {
    if (ImGui::Begin("Brightness/Contrast Node")) {
        ImGui::SliderFloat("Brightness", &brightness, -100.0f, 100.0f);
        ImGui::SliderFloat("Contrast", &contrast, 0.0f, 3.0f);

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

    ImGui::End();
}

void BrightnessContrastNode::UpdateImage() {
    if (!hasInput) return;

    // brightness = beta, contrast = alpha
    inputImage.convertTo(outputImage, -1, contrast, brightness);
    CreateGLTexture();
    needsUpdate = false;
}

const cv::Mat& BrightnessContrastNode::GetOutputImage() const {
    return outputImage;
}

void BrightnessContrastNode::CreateGLTexture() {
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

void BrightnessContrastNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

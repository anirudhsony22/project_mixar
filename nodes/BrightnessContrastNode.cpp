#include <iostream>

#include <opencv2/imgproc.hpp>

#include "BrightnessContrastNode.hpp"
#include "NodeUI.hpp"
#include "SlotUtils.hpp"


BrightnessContrastNode::BrightnessContrastNode(const std::string& name)
    : smkflow::Node(name) {}

void BrightnessContrastNode::SetInputImages(const std::vector<cv::Mat>& images) {
    if (!images.empty() && !images[0].empty()) {
        images[0].copyTo(inputImage);
        hasInput = true;
        needsUpdate = true;
    } else {
        // Clear on disconnect
        inputImage.release();
        outputImage.release();
        hasInput = false;
        needsUpdate = false;
        CleanupTexture();
    }
}


void BrightnessContrastNode::Show(smkflow::Graph& graph) {
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);
    if (ImGui::Begin(("Brightness/Contrast Node: " + name).c_str())) {
        windowPos = ImGui::GetWindowPos();
        windowSize = ImGui::GetWindowSize();

        // Port interaction
        DrawInputPort(*this, 0, graph);
        DrawOutputPort(*this, 0);

        if (hasInput) {
            ImGui::SliderFloat("Brightness", &brightness, -100.0f, 100.0f);
            ImGui::SliderFloat("Contrast", &contrast, 0.0f, 3.0f);

            if (ImGui::Button("Reset Brightness")) brightness = 0.0f;
            ImGui::SameLine();
            if (ImGui::Button("Reset Contrast")) contrast = 1.0f;

            if (ImGui::Button("Update") || ImGui::IsItemDeactivatedAfterEdit()) {
                needsUpdate = true;
            }

            if (needsUpdate) UpdateImage();

            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        } else {
            ImGui::Text("No input image.");
        }
    }
    ImGui::End();
}


void BrightnessContrastNode::UpdateImage() {
    if (!hasInput) return;

    // Apply brightness and contrast adjustments
    inputImage.convertTo(outputImage, -1, contrast, brightness);  // new_image = image*contrast + brightness

    CreateGLTexture();
    needsUpdate = false;
}


const cv::Mat& BrightnessContrastNode::GetOutputImage(int slot = 0) const {
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

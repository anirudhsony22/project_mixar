#include "ThresholdNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include <iostream>

ThresholdNode::ThresholdNode(const std::string& name)
    : smkflow::Node(name) {}

void ThresholdNode::SetInputImages(const std::vector<cv::Mat>& images) {
    if (!images.empty() && !images[0].empty()) {
        images[0].copyTo(inputImage);
        hasInput = true;
        needsUpdate = true;
    } else {
        inputImage.release();
        outputImage.release();
        hasInput = false;
        needsUpdate = false;
        CleanupTexture();
    }
}

const cv::Mat& ThresholdNode::GetOutputImage(int) const {
    return outputImage;
}

void ThresholdNode::Show(smkflow::Graph& graph) {
    if (ImGui::Begin(("Threshold: " + name).c_str())) {
        DrawInputSlot(name, graph);

        if (hasInput) {
            ImGui::SliderInt("Threshold", &thresholdValue, 0, 255);
            ImGui::SliderInt("Max Value", &maxValue, 0, 255);

            const char* methods[] = { "Binary", "Adaptive Mean", "Adaptive Gaussian", "Otsu" };
            ImGui::Combo("Method", &method, methods, IM_ARRAYSIZE(methods));

            if (ImGui::Button("Update") || ImGui::IsItemDeactivatedAfterEdit()) {
                needsUpdate = true;
            }

            if (needsUpdate) UpdateImage();

            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        } else {
            ImGui::Text("No input image.");
        }

        DrawOutputSlot(name, 0);
    }
    ImGui::End();
}

void ThresholdNode::UpdateImage() {
    cv::Mat gray;
    if (inputImage.channels() > 1)
        cv::cvtColor(inputImage, gray, cv::COLOR_RGB2GRAY);
    else
        gray = inputImage;

    switch (method) {
        case 0: // Binary
            cv::threshold(gray, outputImage, thresholdValue, maxValue, cv::THRESH_BINARY);
            break;
        case 1: // Adaptive Mean
            cv::adaptiveThreshold(gray, outputImage, maxValue, cv::ADAPTIVE_THRESH_MEAN_C,
                                  cv::THRESH_BINARY, 11, 2);
            break;
        case 2: // Adaptive Gaussian
            cv::adaptiveThreshold(gray, outputImage, maxValue, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                                  cv::THRESH_BINARY, 11, 2);
            break;
        case 3: // Otsu
            cv::threshold(gray, outputImage, 0, maxValue, cv::THRESH_BINARY | cv::THRESH_OTSU);
            break;
    }

    CreateGLTexture();
    needsUpdate = false;
}

void ThresholdNode::CreateGLTexture() {
    CleanupTexture();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cv::Mat display = EnsureRGB(outputImage);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, display.cols, display.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, display.data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void ThresholdNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

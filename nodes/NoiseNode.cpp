#include "NoiseNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include <random>
#include <iostream>

NoiseNode::NoiseNode(const std::string& name)
    : smkflow::Node(name) {}

const cv::Mat& NoiseNode::GetOutputImage(int) const {
    return outputImage;
}

void NoiseNode::Show(smkflow::Graph& graph) {
    if (ImGui::Begin(("Noise Node: " + name).c_str())) {
        const char* types[] = { "White Noise", "Checkerboard" };
        ImGui::Combo("Type", &noiseType, types, IM_ARRAYSIZE(types));
        ImGui::InputInt("Width", &width);
        ImGui::InputInt("Height", &height);

        if (noiseType == 1) {
            ImGui::SliderInt("Grid Size", &gridSize, 2, 128);
        }

        ImGui::InputInt("Seed", &seed);

        if (ImGui::Button("Generate") || ImGui::IsItemDeactivatedAfterEdit()) {
            needsUpdate = true;
        }

        if (needsUpdate) GenerateNoise();

        if (!outputImage.empty()) {
            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        }

        DrawOutputSlot(name, 0);
    }
    ImGui::End();
}

void NoiseNode::GenerateNoise() {
    outputImage = cv::Mat(height, width, CV_8UC1);

    std::mt19937 rng(seed);

    switch (noiseType) {
        case 0: { // White noise
            std::uniform_int_distribution<> dist(0, 255);
            for (int y = 0; y < outputImage.rows; ++y) {
                for (int x = 0; x < outputImage.cols; ++x) {
                    outputImage.at<uchar>(y, x) = dist(rng);
                }
            }
            break;
        }
        case 1: { // Checkerboard
            for (int y = 0; y < outputImage.rows; ++y) {
                for (int x = 0; x < outputImage.cols; ++x) {
                    int cx = x / gridSize;
                    int cy = y / gridSize;
                    outputImage.at<uchar>(y, x) = ((cx + cy) % 2) ? 255 : 0;
                }
            }
            break;
        }
    }

    cv::cvtColor(outputImage, outputImage, cv::COLOR_GRAY2RGB); // convert for OpenGL
    CreateGLTexture();
    needsUpdate = false;
}

void NoiseNode::CreateGLTexture() {
    CleanupTexture();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, outputImage.cols, outputImage.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, outputImage.data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void NoiseNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

#include "NoiseNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include "SlotUtils.hpp"
#include <random>
#include <iostream>

NoiseNode::NoiseNode(const std::string& name)
    : smkflow::Node(name) {}

const cv::Mat& NoiseNode::GetOutputImage(int) const {
    return outputImage;
}


void NoiseNode::Show(smkflow::Graph& graph) {
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);
    if (ImGui::Begin(("Noise Node: " + name).c_str())) {
        windowPos = ImGui::GetWindowPos();
        windowSize = ImGui::GetWindowSize();

        if (displaceOutput) {
            DrawInputPort(*this, 0, graph);
            ImGui::SliderFloat("Displacement Strength", &displacementStrength, 1.0f, 100.0f);
        }

        ImGui::InputInt("Width", &width);
        ImGui::InputInt("Height", &height);

        const char* types[] = { "White", "Checkerboard", "Perlin", "Simplex", "Worley" };
        ImGui::Combo("Noise Type", &noiseType, types, IM_ARRAYSIZE(types));
        ImGui::SliderFloat("Scale", &scale, 0.005f, 0.2f);
        ImGui::SliderInt("Octaves", &octaves, 1, 6);
        ImGui::SliderFloat("Persistence", &persistence, 0.1f, 1.0f);
        ImGui::Checkbox("Displace Output", &displaceOutput);

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

        DrawOutputPort(*this, 0);  // always has an output
    }
    ImGui::End();
}


void NoiseNode::GenerateNoise() {
    // Step 1: Generate base noise (1-channel grayscale)
    cv::Mat noise(height, width, CV_8UC1);

    fn.SetSeed(seed);
    fn.SetFractalOctaves(octaves);
    fn.SetFractalLacunarity(2.0f);
    fn.SetFractalGain(persistence);
    fn.SetFrequency(scale);

    switch (noiseType) {
        case PERLIN:
            fn.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
            break;
        case SIMPLEX:
            fn.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
            break;
        case WORLEY:
            fn.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
            break;
        default:
            fn.SetNoiseType(FastNoiseLite::NoiseType_Value);
            break;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float nx = static_cast<float>(x) / width;
            float ny = static_cast<float>(y) / height;
            float value = fn.GetNoise(nx * width, ny * height); // [-1, 1]
            value = (value + 1.0f) * 0.5f * 255.0f;              // [0, 255]
            noise.at<uchar>(y, x) = static_cast<uchar>(value);
        }
    }

    // Step 2: Displacement (if enabled and input image is present)
    if (displaceOutput && !displacementSource.empty()) {
        cv::Mat mapX(height, width, CV_32F);
        cv::Mat mapY(height, width, CV_32F);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float n = noise.at<uchar>(y, x) / 255.0f; // [0, 1]
                float dx = (n - 0.5f) * 2.0f * displacementStrength;
                float dy = (n - 0.5f) * 2.0f * displacementStrength;

                float newX = std::clamp<float>(x + dx, 0, width - 1);
                float newY = std::clamp<float>(y + dy, 0, height - 1);

                mapX.at<float>(y, x) = newX;
                mapY.at<float>(y, x) = newY;
            }
        }

        cv::remap(displacementSource, outputImage, mapX, mapY, cv::INTER_LINEAR);
    } else {
        // Use noise directly as output
        cv::cvtColor(noise, outputImage, cv::COLOR_GRAY2RGB);
    }

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


void NoiseNode::SetInputImages(const std::vector<cv::Mat>& images) {
    if (!images.empty() && !images[0].empty()) {
        displacementSource = EnsureRGB(images[0]);
    } else {
        displacementSource.release();
    }
}

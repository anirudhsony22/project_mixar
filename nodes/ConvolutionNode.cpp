#include "ConvolutionNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include "SlotUtils.hpp"
#include <iostream>

ConvolutionNode::ConvolutionNode(const std::string& name)
    : smkflow::Node(name) {}

void ConvolutionNode::SetInputImages(const std::vector<cv::Mat>& images) {
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


const cv::Mat& ConvolutionNode::GetOutputImage(int) const {
    return outputImage;
}


void ConvolutionNode::Show(smkflow::Graph& graph) {
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);
    if (ImGui::Begin(("Convolution: " + name).c_str())) {
        windowPos = ImGui::GetWindowPos();
        windowSize = ImGui::GetWindowSize();

        // === Port interactions ===
        DrawInputPort(*this, 0, graph);
        DrawOutputPort(*this, 0);

        if (hasInput) {
            // Preset selection
            const char* presets[] = { "Custom", "Sharpen", "Edge Enhance", "Emboss" };
            if (ImGui::Combo("Preset", &selectedPreset, presets, IM_ARRAYSIZE(presets))) {
                ApplyPreset(selectedPreset);
                needsUpdate = true;
            }

            ImGui::Checkbox("Use 5x5 Kernel", &use5x5);

            // Kernel editor
            int size = use5x5 ? 5 : 3;
            float (*kernelPtr)[5] = use5x5 ? kernel5x5 : (float(*)[5])kernel3x3;

            for (int i = 0; i < size; ++i) {
                ImGui::PushID(i);
                for (int j = 0; j < size; ++j) {
                    ImGui::PushID(j);
                    ImGui::SetNextItemWidth(40);
                    ImGui::DragFloat("##k", &kernelPtr[i][j], 0.1f);
                    ImGui::SameLine();
                    ImGui::PopID();
                }
                ImGui::NewLine();
                ImGui::PopID();
            }

            ImGui::Checkbox("Normalize", &normalize);

            if (ImGui::Button("Update") || ImGui::IsItemDeactivatedAfterEdit()) {
                needsUpdate = true;
            }

            if (needsUpdate) UpdateImage();

            if (!outputImage.empty()) {
                ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
            }
        } else {
            ImGui::Text("No input image.");
        }
    }
    ImGui::End();
}


void ConvolutionNode::ApplyPreset(int presetIndex) {
    if (use5x5) {
        switch (presetIndex) {
            case 1: // Sharpen (center-heavy)
                std::memset(kernel5x5, 0, sizeof(kernel5x5));
                kernel5x5[2][2] = 9;
                kernel5x5[1][2] = kernel5x5[2][1] = kernel5x5[2][3] = kernel5x5[3][2] = -2;
                break;
            case 2: // Edge Enhance
                for (int i = 0; i < 5; ++i)
                    for (int j = 0; j < 5; ++j)
                        kernel5x5[i][j] = 1;
                kernel5x5[2][2] = -24;
                break;
            case 3: // Emboss
                std::memset(kernel5x5, 0, sizeof(kernel5x5));
                kernel5x5[0][0] = -2; kernel5x5[0][1] = -1;
                kernel5x5[1][0] = -1; kernel5x5[2][2] = 1;
                kernel5x5[3][3] = 1;  kernel5x5[4][4] = 2;
                break;
        }
    } else {
        switch (presetIndex) {
            case 1: // Sharpen
                kernel3x3[0][0] = 0;  kernel3x3[0][1] = -1; kernel3x3[0][2] = 0;
                kernel3x3[1][0] = -1; kernel3x3[1][1] = 5;  kernel3x3[1][2] = -1;
                kernel3x3[2][0] = 0;  kernel3x3[2][1] = -1; kernel3x3[2][2] = 0;
                break;
            case 2: // Edge Enhance
                kernel3x3[0][0] = 1;  kernel3x3[0][1] = 1;  kernel3x3[0][2] = 1;
                kernel3x3[1][0] = 1;  kernel3x3[1][1] = -7; kernel3x3[1][2] = 1;
                kernel3x3[2][0] = 1;  kernel3x3[2][1] = 1;  kernel3x3[2][2] = 1;
                break;
            case 3: // Emboss
                kernel3x3[0][0] = -2; kernel3x3[0][1] = -1; kernel3x3[0][2] = 0;
                kernel3x3[1][0] = -1; kernel3x3[1][1] = 1;  kernel3x3[1][2] = 1;
                kernel3x3[2][0] = 0;  kernel3x3[2][1] = 1;  kernel3x3[2][2] = 2;
                break;
        }
    }
}


void ConvolutionNode::UpdateImage() {
    if (!hasInput || inputImage.empty()) return;

    int ksize = use5x5 ? 5 : 3;
    cv::Mat kernelMat(ksize, ksize, CV_32F, use5x5 ? (void*)kernel5x5 : (void*)kernel3x3);
    if (normalize) kernelMat /= cv::sum(kernelMat)[0];

    cv::filter2D(inputImage, outputImage, -1, kernelMat);

    CreateGLTexture();
    needsUpdate = false;
}


void ConvolutionNode::CreateGLTexture() {
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


void ConvolutionNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

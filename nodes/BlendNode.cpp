#include "BlendNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include "SlotUtils.hpp"
#include <iostream>

BlendNode::BlendNode(const std::string& name)
    : smkflow::Node(name) {}

void BlendNode::SetInputImages(const std::vector<cv::Mat>& images) {
    inputImages = images;
    hasInput = images.size() == 2 && !images[0].empty() && !images[1].empty();
    needsUpdate = hasInput;
}


const cv::Mat& BlendNode::GetOutputImage(int) const {
    return outputImage;
}


void BlendNode::Show(smkflow::Graph& graph) {
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);

    if (ImGui::Begin(("Blend: " + name).c_str())) {
        // Track window position & size for edge layout
        windowPos = ImGui::GetWindowPos();
        windowSize = ImGui::GetWindowSize();

        // === Port bubbles ===
        DrawInputPort(*this, 0, graph);
        DrawInputPort(*this, 1, graph);
        DrawOutputPort(*this, 0);

        // === Node controls ===
        const char* modes[] = { "Normal", "Multiply", "Screen", "Overlay", "Difference" };
        ImGui::Combo("Mode", &blendMode, modes, IM_ARRAYSIZE(modes));

        if (blendMode == 0) {
            ImGui::SliderFloat("Blend Factor", &blendFactor, 0.0f, 1.0f);
        }

        if (ImGui::Button("Update") || ImGui::IsItemDeactivatedAfterEdit()) {
            needsUpdate = true;
        }

        if (hasInput && needsUpdate) {
            UpdateImage();
        }

        if (!outputImage.empty()) {
            ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
        } else {
            ImGui::Text("Waiting for two valid inputs.");
        }
    }

    ImGui::End();
}


void BlendNode::UpdateImage() {
    if (inputImages.size() != 2 || inputImages[0].empty() || inputImages[1].empty()) return;

    cv::Mat a = EnsureRGB(inputImages[0]);
    cv::Mat b = EnsureRGB(inputImages[1]);
    cv::resize(b, b, a.size());

    switch (blendMode) {
        case 0: // Normal
            cv::addWeighted(a, 1.0f - blendFactor, b, blendFactor, 0, outputImage);
            break;
        case 1: // Multiply
            cv::multiply(a, b, outputImage, 1.0 / 255.0);
            outputImage.convertTo(outputImage, CV_8U);
            break;
        case 2: // Screen
            outputImage = 255 - ((255 - a).mul(255 - b) / 255);
            break;
        case 3: // Overlay
            outputImage = a.clone();
            for (int y = 0; y < a.rows; ++y) {
                for (int x = 0; x < a.cols; ++x) {
                    for (int c = 0; c < 3; ++c) {
                        float va = a.at<cv::Vec3b>(y, x)[c] / 255.0f;
                        float vb = b.at<cv::Vec3b>(y, x)[c] / 255.0f;
                        float result = (va < 0.5f) ? (2 * va * vb) : (1 - 2 * (1 - va) * (1 - vb));
                        outputImage.at<cv::Vec3b>(y, x)[c] = static_cast<uchar>(result * 255);
                    }
                }
            }
            break;
        case 4: // Difference
            cv::absdiff(a, b, outputImage);
            break;
    }

    CreateGLTexture();
    needsUpdate = false;
}


void BlendNode::CreateGLTexture() {
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


void BlendNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

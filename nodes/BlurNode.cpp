#include <iostream>

#include <opencv2/imgproc.hpp>

#include "BlurNode.hpp"
#include "NodeUI.hpp"


BlurNode::BlurNode(const std::string& name)
    : smkflow::Node(name) {}

void BlurNode::SetInputImages(const std::vector<cv::Mat>& images) {
    if (!images.empty() && !images[0].empty()) {
        images[0].copyTo(inputImage);
        hasInput = true;
        needsUpdate = true;
    } else {
        // Clear state on disconnect
        inputImage.release();
        outputImage.release();
        hasInput = false;
        needsUpdate = false;
        CleanupTexture();
    }
}
    
void BlurNode::Show(smkflow::Graph& graph) {
    if (ImGui::Begin(("Blur Node: " + name).c_str())) {
        DrawInputSlot(name, graph);

        if (hasInput) {
            const char* blurModes[] = { "Gaussian", "Box (Uniform)", "Directional" };
            ImGui::Combo("Blur Type", &blurType, blurModes, IM_ARRAYSIZE(blurModes));
            ImGui::SliderInt("Radius", &blurRadius, 1, 20);
            if (blurRadius % 2 == 0) blurRadius += 1;

            if (blurType == 2) {
                const char* directions[] = { "Horizontal", "Vertical" };
                ImGui::Combo("Direction", &direction, directions, IM_ARRAYSIZE(directions));
            }

            if (ImGui::Button("Update") || ImGui::IsItemDeactivatedAfterEdit()) {
                needsUpdate = true;
            }

            if (needsUpdate) {
                UpdateImage();
            }

            if (!outputImage.empty()) {
                ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));
            }

        } else {
            ImGui::Text("No input image.");
        }

        DrawOutputSlot(name,0);
    }
    ImGui::End();
}


void BlurNode::UpdateImage() {
    if (!hasInput) return;

    switch (blurType) {
        case 0: // Gaussian
            cv::GaussianBlur(inputImage, outputImage, cv::Size(blurRadius, blurRadius), 0);
            break;
        case 1: // Box (Uniform)
            cv::blur(inputImage, outputImage, cv::Size(blurRadius, blurRadius));
            break;
        case 2: { // Directional
            int kx = direction == 0 ? blurRadius : 1;
            int ky = direction == 1 ? blurRadius : 1;
            cv::blur(inputImage, outputImage, cv::Size(kx, ky));
            break;
        }
    }
    CreateGLTexture();
    needsUpdate = false;
}

const cv::Mat& BlurNode::GetOutputImage(int slot = 0) const {
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

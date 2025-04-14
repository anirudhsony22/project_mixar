#include "EdgeDetectionNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include <iostream>

EdgeDetectionNode::EdgeDetectionNode(const std::string& name)
    : smkflow::Node(name) {}

void EdgeDetectionNode::SetInputImages(const std::vector<cv::Mat>& images) {
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

const cv::Mat& EdgeDetectionNode::GetOutputImage(int) const {
    return outputImage;
}

void EdgeDetectionNode::Show(smkflow::Graph& graph) {
    if (ImGui::Begin(("Edge Detection: " + name).c_str())) {
        DrawInputSlot(name, graph);

        if (hasInput) {
            const char* methods[] = { "Sobel", "Canny" };
            ImGui::Combo("Method", &method, methods, IM_ARRAYSIZE(methods));

            if (method == 0) { // Sobel
                ImGui::SliderInt("dx", &sobelDx, 0, 2);
                ImGui::SliderInt("dy", &sobelDy, 0, 2);
                ImGui::SliderInt("Kernel Size", &sobelKernel, 1, 7);
                if (sobelKernel % 2 == 0) sobelKernel += 1;
            } else { // Canny
                ImGui::SliderInt("Threshold1", &cannyThreshold1, 0, 255);
                ImGui::SliderInt("Threshold2", &cannyThreshold2, 0, 255);
            }

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

void EdgeDetectionNode::UpdateImage() {
    cv::Mat gray;
    if (inputImage.channels() > 1)
        cv::cvtColor(inputImage, gray, cv::COLOR_RGB2GRAY);
    else
        gray = inputImage;

    if (method == 0) { // Sobel
        cv::Sobel(gray, outputImage, CV_8U, sobelDx, sobelDy, sobelKernel);
    } else { // Canny
        cv::Canny(gray, outputImage, cannyThreshold1, cannyThreshold2);
    }

    CreateGLTexture();
    needsUpdate = false;
}

void EdgeDetectionNode::CreateGLTexture() {
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

void EdgeDetectionNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

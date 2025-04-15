#include "ThresholdNode.hpp"
#include "NodeUI.hpp"
#include "ImageUtils.hpp"
#include "SlotUtils.hpp"
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
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);
    if (ImGui::Begin(("Threshold: " + name).c_str())) {
        windowPos = ImGui::GetWindowPos();
        windowSize = ImGui::GetWindowSize();

        DrawInputPort(*this, 0, graph);
        DrawOutputPort(*this, 0);

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

            const char* scaleModes[] = { "Linear", "Log Scale" };
            ImGui::Combo("Histogram Scale", &histScaleMode, scaleModes, IM_ARRAYSIZE(scaleModes));

            if (histogramReady) {
                ImGui::Text("Histogram");
                ImGui::PlotLines("##hist", histogram, 256, 0, nullptr, 0.0f, 1.0f, ImVec2(256, 100));

                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImDrawList* drawList = ImGui::GetWindowDrawList();

                float xUser = pos.x + (thresholdValue / 255.0f) * 256.0f;
                drawList->AddLine(ImVec2(xUser, pos.y - 100), ImVec2(xUser, pos.y), IM_COL32(255, 0, 0, 255), 2.0f);

                if (method == 3 && otsuComputedValue >= 0) {
                    float xOtsu = pos.x + (otsuComputedValue / 255.0f) * 256.0f;
                    drawList->AddLine(ImVec2(xOtsu, pos.y - 100), ImVec2(xOtsu, pos.y), IM_COL32(255, 255, 0, 255), 2.0f);
                    ImGui::Text("Otsu Threshold: %d", otsuComputedValue);
                }
            }

        } else {
            ImGui::Text("No input image.");
        }
    }
    ImGui::End();
}


void ThresholdNode::UpdateImage() {
    cv::Mat gray;
    if (inputImage.channels() > 1)
        cv::cvtColor(inputImage, gray, cv::COLOR_RGB2GRAY);
    else
        gray = inputImage;

    // === Compute Histogram ===
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };

    cv::Mat hist;
    cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    double maxVal;
    cv::minMaxLoc(hist, 0, &maxVal);

    for (int i = 0; i < histSize; ++i) {
        float value = hist.at<float>(i);
    
        if (histScaleMode == 1) { // Log scale
            histogram[i] = static_cast<float>(std::log1p(value) / std::log1p(maxVal));
        } else { // Linear
            histogram[i] = static_cast<float>(value / (maxVal > 0 ? maxVal : 1));
        }
    }

    histogramReady = true;

    // === Thresholding ===
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
            otsuComputedValue = static_cast<int>(
                cv::threshold(gray, outputImage, 0, maxValue, cv::THRESH_BINARY | cv::THRESH_OTSU)
            );
        
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


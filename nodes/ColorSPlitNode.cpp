#include <iostream>

#include "ColorSplitNode.hpp"
#include "NodeUI.hpp"

ColorSplitNode::ColorSplitNode(const std::string& name)
    : smkflow::Node(name) {}

void ColorSplitNode::SetInputImages(const std::vector<cv::Mat>& images) {
    if (!images.empty() && !images[0].empty()) {
        images[0].copyTo(inputImage);
        hasInput = true;
        needsUpdate = true;
    } else {
        inputImage.release();
        channelR.release(); channelG.release(); channelB.release();
        hasInput = false;
        needsUpdate = false;
        CleanupTextures();
    }
}

const cv::Mat& ColorSplitNode::GetOutputImage(int slot) const {
    if (slot == 1) return channelG;
    if (slot == 2) return channelB;
    return channelR;  // default
}


void ColorSplitNode::Show(smkflow::Graph& graph) {
    if (ImGui::Begin(("Color Split: " + name).c_str())) {
        DrawInputSlot(name, graph);

        if (hasInput) {
            if (needsUpdate) UpdateImages();

            ImGui::Text("R Channel");
            ImVec2 rPos = ImGui::GetCursorScreenPos();
            ImGui::Image((ImTextureID)(uintptr_t)texR, ImVec2(100, 100));
            DrawOutputSlot(name, 0);

            ImGui::Text("G Channel");
            ImVec2 gPos = ImGui::GetCursorScreenPos();
            ImGui::Image((ImTextureID)(uintptr_t)texG, ImVec2(100, 100));
            DrawOutputSlot(name, 1);

            ImGui::Text("B Channel");
            ImVec2 bPos = ImGui::GetCursorScreenPos();
            ImGui::Image((ImTextureID)(uintptr_t)texB, ImVec2(100, 100));
            DrawOutputSlot(name, 2);

        } else {
            ImGui::Text("No input image.");
        }

        DrawOutputSlot(name, 0);
    }
    ImGui::End();
}

void ColorSplitNode::UpdateImages() {
    std::vector<cv::Mat> channels;
    cv::split(inputImage, channels);

    if (channels.size() >= 3) {
        channelB = channels[0];
        channelG = channels[1];
        channelR = channels[2];

        CreateGLTexture(texR, channelR, 'R');
        CreateGLTexture(texG, channelG, 'G');
        CreateGLTexture(texB, channelB, 'B');
    }

    needsUpdate = false;
}

void ColorSplitNode::CreateGLTexture(GLuint& texID, const cv::Mat& channel, char tint) {
    if (texID) glDeleteTextures(1, &texID);

    // Create a colored version of the channel
    std::vector<cv::Mat> rgbChannels(3);
    cv::Mat zero = cv::Mat::zeros(channel.size(), CV_8UC1);

    if (tint == 'R') {
        rgbChannels = { channel, zero, zero }; // B, G, R
    } else if (tint == 'G') {
        rgbChannels = { zero, channel, zero };
    } else { // 'B'
        rgbChannels = { zero, zero, channel };
    }

    cv::Mat rgb;
    cv::merge(rgbChannels, rgb); // BGR order for OpenCV

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rgb.cols, rgb.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, rgb.data);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void ColorSplitNode::CleanupTextures() {
    if (texR) glDeleteTextures(1, &texR); texR = 0;
    if (texG) glDeleteTextures(1, &texG); texG = 0;
    if (texB) glDeleteTextures(1, &texB); texB = 0;
}

#include "outputNode.hpp"
#include <opencv2/imgcodecs.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

OutputNode::OutputNode() {}

void OutputNode::SetInputImage(const cv::Mat& input) {
    if (input.empty()) return;
    input.copyTo(image);
    hasImage = true;
    CreateGLTexture();
}

void OutputNode::Show() {
    ImGui::Begin("Output Node");

    if (hasImage) {
        ImGui::Text("Preview:");
        ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(128, 128));

        const char* formats[] = {"png", "jpg", "bmp"};
        static int current = 0;
        ImGui::Combo("Format", &current, formats, IM_ARRAYSIZE(formats));
        format = formats[current];

        if (ImGui::Button("Save Image")) {
            SaveImage();
        }
    } else {
        ImGui::Text("No image input");
    }

    ImGui::End();
}

void OutputNode::SaveImage() {
    std::string path = "output_image." + format;
    cv::Mat saveImg;
    if (image.channels() == 4)
        cv::cvtColor(image, saveImg, cv::COLOR_RGBA2BGRA);
    else
        cv::cvtColor(image, saveImg, cv::COLOR_RGB2BGR);

    if (cv::imwrite(path, saveImg)) {
        std::cout << "Saved to " << path << std::endl;
    } else {
        std::cerr << "Failed to save image!" << std::endl;
    }
}

void OutputNode::CreateGLTexture() {
    CleanupTexture();
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLenum format = image.channels() == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.cols, image.rows, 0, format, GL_UNSIGNED_BYTE, image.data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OutputNode::CleanupTexture() {
    if (textureID) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

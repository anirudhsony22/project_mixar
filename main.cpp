#define GL_SILENCE_DEPRECATION

#include <smkflow/Graph.hpp>
#include <smkflow/Theme.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "nodes/ImageInputNode.hpp"
#include "nodes/OutputNode.hpp"
#include "nodes/BrightnessContrastNode.hpp"
#include "nodes/BlurNode.hpp"
#include "graph/GraphExecutor.hpp"

#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    // Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return -1;

    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS requirement

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Node-Based Image Editor", nullptr, nullptr);
    if (window == nullptr) return -1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Build graph
    smkflow::Graph graph;

    auto* inputGraphNode  = graph.AddNode("Image Input");
    auto* blurGraphNode   = graph.AddNode("Blur");
    auto* bcGraphNode     = graph.AddNode("Brightness/Contrast");
    auto* outputGraphNode = graph.AddNode("Output");

    // Connect graph: Input -> Blur -> Brightness -> Output
    blurGraphNode->ConnectTo(inputGraphNode);
    bcGraphNode->ConnectTo(blurGraphNode);
    outputGraphNode->ConnectTo(bcGraphNode);

    // Create real nodes
    static ImageInputNode imageNode;
    static BlurNode blurNode;
    static BrightnessContrastNode bcNode;
    static OutputNode outputNode;

    // Map graph nodes to real image-processing nodes
    std::unordered_map<smkflow::Node*, BaseImageNode*> imageNodeMap;
    imageNodeMap[inputGraphNode]  = &imageNode;
    imageNodeMap[blurGraphNode]   = &blurNode;
    imageNodeMap[bcGraphNode]     = &bcNode;
    imageNodeMap[outputGraphNode] = &outputNode;

    GraphExecutor executor;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        smkflow::Theme_Default();
        graph.Show();

        executor.Evaluate(graph, imageNodeMap);

        blurNode.SetInputImage(imageNode.GetOutputImage());
        // blurNode.Show();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
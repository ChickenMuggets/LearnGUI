#include "../includes/imgui/imgui.h"
#include "GLFW/glfw3.h"
#include "../includes/imgui/imgui_impl_glfw.h"
#include "../includes/imgui/imgui_impl_opengl3.h"
#include "node.h"
#include <iostream>

namespace node {
    void window(bool& nodeOpen, GLFWwindow* window) {
        std::cout << "node opened\n";
        // Create UI
        ImGui::Begin("Node Window", &nodeOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::BeginGroup();
        ImGui::Text("Node Title");
        
        // Move the close button to the top-right
        ImGui::SameLine(ImGui::GetWindowWidth() - 30);
        if (ImGui::Button("X")) {
            // Instead of directly cleaning up,
            // set the flag to close the window.
            glfwSetWindowShouldClose(window, 1);
        }
        ImGui::EndGroup();
        
        ImGui::Separator();
        
        ImGui::Text("Hello, GLFW + ImGui!");
        ImGui::End(); // End the "Node Window" that was begun above.
    }
}
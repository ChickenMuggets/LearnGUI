#include "../includes/imgui/imgui.h"
#include "GLFW/glfw3.h"
#include "../includes/imgui/imgui_impl_glfw.h"
#include "../includes/imgui/imgui_impl_opengl3.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) return -1;

    // Create a hidden GLFW window by setting GLFW_VISIBLE to GLFW_FALSE
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE); // Prevents flickering focus issues

    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui + GLFW", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync
    
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Enable Multi-Viewport to allow windows to exit the main window
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    bool nodeOpen = true; // Track node state
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create UI
        ImGui::Begin("Node Window", &nodeOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::BeginGroup(); 
        ImGui::Text("Node Title");
    
        // Move the close button to the top-right
        ImGui::SameLine(ImGui::GetWindowWidth() - 30);
        if (ImGui::Button("X")) {
            // Cleanup
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwDestroyWindow(window);
            glfwTerminate();
        }
        ImGui::EndGroup();
        
        ImGui::Separator(); // Visual separation between title and content

        ImGui::Text("Hello, GLFW + ImGui!");
        
        ImGui::End();

        // Render main viewport
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Handle multiple viewports to prevent flickering
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_context);
        }

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

#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Interface {
    GLFWwindow* window;
    const char* gDefaultConfigPath = "config.ini";
    int gConfig = 1;

    void InitWindow() {
        // 初始化GLFW库
        glfwInit();

        // 设置窗口相关参数
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // 创建窗口
        window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        // 初始化OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // 初始化Dear ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
    }

    void RenderMenu() {
        // 在菜单栏中添加一个选项
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    // 处理打开文件事件
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void RenderContent() {
        // 渲染窗口内容
        ImGui::Begin("My Window");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }

    void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // 处理键盘事件
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void Run() {
        InitWindow();

        // 渲染循环
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            // 渲染菜单栏和窗口内容
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            RenderMenu();
            RenderContent();

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        // 处理键盘事件
            glfwSetKeyCallback(window, ProcessInput);
        }

        // 清理Dear ImGui和GLFW
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }
}

int main() {
    Interface::Run();
    return 0;
}
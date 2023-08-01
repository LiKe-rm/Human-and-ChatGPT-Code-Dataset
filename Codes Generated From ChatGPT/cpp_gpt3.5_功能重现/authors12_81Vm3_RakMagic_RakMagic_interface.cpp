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
        // ��ʼ��GLFW��
        glfwInit();

        // ���ô�����ز���
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // ��������
        window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        // ��ʼ��OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // ��ʼ��Dear ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
    }

    void RenderMenu() {
        // �ڲ˵��������һ��ѡ��
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    // ������ļ��¼�
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void RenderContent() {
        // ��Ⱦ��������
        ImGui::Begin("My Window");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }

    void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // ��������¼�
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void Run() {
        InitWindow();

        // ��Ⱦѭ��
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            // ��Ⱦ�˵����ʹ�������
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
        // ��������¼�
            glfwSetKeyCallback(window, ProcessInput);
        }

        // ����Dear ImGui��GLFW
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
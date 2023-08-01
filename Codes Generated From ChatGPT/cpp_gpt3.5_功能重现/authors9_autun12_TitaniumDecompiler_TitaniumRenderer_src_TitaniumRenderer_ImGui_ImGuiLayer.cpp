#include "ImGuiLayer.h"
#include "TitaniumRenderer/Core/Application.h"

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

namespace TitaniumRenderer {

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::OnAttach() {
        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup ImGui style
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup platform/renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event& e) {
        if (m_BlockEvents) {
            ImGuiIO& io = ImGui::GetIO();
            e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }
    }

    void ImGuiLayer::SetDarkThemeColors() {
        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4 {0.1f, 0.105f, 0.11f, 1.0f};

        // Headers
        colors[ImGuiCol_Header] = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        // Frame Background
        colors[ImGuiCol_FrameBg] = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4 {0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4 {0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};

        // Sliders
        colors[ImGuiCol_SliderGrab] = ImVec4 {0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_SliderGrabActive] = ImVec4 {0.38f, 0.3805f, 0.381f, 1.0f};

        // Checkboxes
        colors[ImGuiCol_CheckMark] = ImVec4 {0.8f, 0.805f, 0.81f, 1.0f};

        // Menus
        colors[ImGuiCol_MenuBarBg] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_PopupBg] = ImVec4 {0.1f, 0.105f, 0.11f, 1.0f};

        // Scrolling
        colors[ImGuiCol_ScrollbarBg] = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ScrollbarGrab] = ImVec4 {0.3f, 0.305f, 031f, 1.0f};
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4 {0.4f, 0.405f, 0.41f, 1.0f};
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4 {0.5f, 0.505f, 0.51f, 1.0f};
        // Text
        colors[ImGuiCol_Text] = ImVec4 {0.8f, 0.805f, 0.81f, 1.0f};
        colors[ImGuiCol_TextDisabled] = ImVec4 {0.6f, 0.605f, 0.61f, 1.0f};
        colors[ImGuiCol_TextSelectedBg] = ImVec4 {0.7f, 0.705f, 0.71f, 1.0f};

        // Separators
        colors[ImGuiCol_Separator] = ImVec4 {0.5f, 0.505f, 0.51f, 1.0f};
        colors[ImGuiCol_SeparatorHovered] = ImVec4 {0.6f, 0.605f, 0.61f, 1.0f};
        colors[ImGuiCol_SeparatorActive] = ImVec4 {0.7f, 0.705f, 0.71f, 1.0f};

        // Borders
        colors[ImGuiCol_Border] = ImVec4 {0.4f, 0.405f, 0.41f, 1.0f};
        colors[ImGuiCol_BorderShadow] = ImVec4 {0.0f, 0.0f, 0.0f, 0.0f};

        // Plotting
        colors[ImGuiCol_PlotLines] = ImVec4 {0.9f, 0.905f, 0.91f, 1.0f};
        colors[ImGuiCol_PlotLinesHovered] = ImVec4 {1.0f, 1.0f, 1.0f, 1.0f};
        colors[ImGuiCol_PlotHistogram] = ImVec4 {0.9f, 0.905f, 0.91f, 1.0f};
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4 {1.0f, 1.0f, 1.0f, 1.0f};
    }

} // namespace TitaniumRenderer
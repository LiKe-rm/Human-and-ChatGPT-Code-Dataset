#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "TitaniumLayer.h"
#include "Event.h"
#include "KeyCodes.h"
#include "Log.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace fs = std::filesystem;

class TitaniumLayer: public Layer {
public:
    TitaniumLayer()
        : Layer("TitaniumLayer") {
    }

    virtual ~TitaniumLayer() {
    }

    void OnAttach() override {
        TI_INFO("TitaniumLayer attached");
        m_Console.Init();

        // Initialize mask and add it to core and client loggers' receivers
        auto mask = LogMask(LogSeverity::Trace);
        Log::GetCoreLogger()->AddReceiver(m_Console.GetLogReceiver(mask));
        Log::GetClientLogger()->AddReceiver(m_Console.GetLogReceiver(mask));
    }

    void OnDetach() override {
        TI_INFO("TitaniumLayer detached");
    }

    void OnUpdate() override {
        // Set background color and clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OnImGuiRender() override {
        m_Console.Draw();
        DrawHexView();
        DrawMainMenu();
    }

    void OnEvent(Event& event) override {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&TitaniumLayer::OnKeyPressed, this, std::placeholders::_1));
    }

    bool OnKeyPressed(KeyPressedEvent& event) {
        if (event.GetKeyCode() == TI_KEY_CTRL) {
            m_CtrlPressed = true;
        }
        if (m_CtrlPressed && event.GetKeyCode() == TI_KEY_O) {
            OpenAnalyzeFile();
        }
        return false;
    }

private:
    void OpenAnalyzeFile() {
        // Open a file browser and select a file to open
        std::string filePath = ""; // Implement a file browser logic here
        if (!filePath.empty()) {
            std::ifstream file(filePath, std::ios::binary);
            if (file.is_open()) {
                TI_INFO("File opened: {0}", filePath);
                m_HexData.clear();
                std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(m_HexData));
                file.close();
            } else {
                TI_ERROR("Failed to open file: {0}", filePath);
            }
        }
    }

    void DrawHexView() {
        // Implement Hex View panel here
    }

    void DrawMainMenu() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open", "CTRL+O")) {
                    OpenAnalyzeFile();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

private:
    bool m_CtrlPressed = false;
    Console m_Console;
    std::vector<uint8_t> m_HexData;
};

int main(int argc, char** argv) {
    Log::Init();
    TI_CORE_INFO("Initialized Log!");

    auto app = std::make_unique<Application>();
    app->PushLayer(std::make_unique<TitaniumLayer>());
    app->Run();

    return 0;
}

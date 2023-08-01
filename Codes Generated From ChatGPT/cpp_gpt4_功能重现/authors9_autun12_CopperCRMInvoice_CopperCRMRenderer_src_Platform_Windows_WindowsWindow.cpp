#include <iostream>
#include <GLFW/glfw3.h>

class WindowsWindow {
public:
    struct WindowData {
        int width, height;
        std::string title;
        GLFWwindow* window;
        bool shouldClose;

        WindowData(int w, int h, const std::string& t)
            : width(w), height(h), title(t), window(nullptr), shouldClose(false) {}
    };

    WindowsWindow(int width, int height, const std::string& title) {
        init(width, height, title);
    }

    ~WindowsWindow() {
        shutdown();
    }

    void update() {
        processInput();
        glfwSwapBuffers(m_data.window);
        glfwPollEvents();
    }

    bool shouldClose() const {
        return m_data.shouldClose;
    }

private:
    void init(int width, int height, const std::string& title) {
        m_data = WindowData(width, height, title);

        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_data.window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);

        if (!m_data.window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_data.window);
        glfwSetWindowUserPointer(m_data.window, &m_data);

        glfwSetFramebufferSizeCallback(m_data.window, [](GLFWwindow* window, int width, int height) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data->width = width;
            data->height = height;
            glViewport(0, 0, width, height);
        });

        glfwSetWindowCloseCallback(m_data.window, [](GLFWwindow* window) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data->shouldClose = true;
        });
    }

    void shutdown() {
        glfwDestroyWindow(m_data.window);
        glfwTerminate();
    }

    void processInput() {
        if (glfwGetKey(m_data.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            m_data.shouldClose = true;
        }
    }

private:
    WindowData m_data;
};

int main() {
    WindowsWindow window(800, 600, "OpenGL Demo");

    while (!window.shouldClose()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.update();
    }

    return 0;
}

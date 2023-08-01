#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h> // For glfwGetWin32Window
#endif

#define HAS_GLFW_VERSION_3_3_OR_GREATER ((GLFW_VERSION_MAJOR > 3) || (GLFW_VERSION_MAJOR == 3 && GLFW_VERSION_MINOR >= 3))

enum GlfwClientApi
{
	GlfwClientApi_Unknown,
	GlfwClientApi_OpenGL,
	GlfwClientApi_Vulkan
};

// Global variables and function pointers
GLFWwindow* g_Window = nullptr;
GlfwClientApi g_ClientApi = GlfwClientApi_Unknown;
double g_Time = 0.0;
bool g_MouseJustPressed[ImGuiMouseButton_COUNT] = {};
GLFWcursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = {};

// Clipboard functions
const char* ImGui_ImplGlfw_GetClipboardText(void*)
{
	return glfwGetClipboardString(g_Window);
}

void ImGui_ImplGlfw_SetClipboardText(void*, const char* text)
{
	glfwSetClipboardString(g_Window, text);
}

// GLFW callbacks
void ImGui_ImplGlfw_MouseButtonCallback(GLFWwindow*, int button, int action, int /*mods*/)
{
	if (action == GLFW_PRESS)
		g_MouseJustPressed[button] = true;
}

void ImGui_ImplGlfw_ScrollCallback(GLFWwindow*, double xoffset, double yoffset)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += (float)xoffset;
	io.MouseWheel += (float)yoffset;
}

void ImGui_ImplGlfw_KeyCallback(GLFWwindow*, int key, int, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	if (action == GLFW_PRESS)
		io.KeysDown[key] = true;
	if (action == GLFW_RELEASE)
		io.KeysDown[key] = false;

	// Modifiers are not reliable across systems
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}

void ImGui_ImplGlfw_CharCallback(GLFWwindow*, unsigned int c)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddInputCharacter(c);
}

bool ImGui_ImplGlfw_Init(GLFWwindow* window, bool install_callbacks, GlfwClientApi client_api)
{
	g_Window = window;
	g_Time = 0.0;

	// Setup backend capabilities flags
	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
	io.BackendPlatformName = "imgui_impl_glfw";

	// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;

	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
	io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
	io.ClipboardUserData = nullptr;

	// Create mouse cursors
	g_MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	g_MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
	g_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR); // FIXME: GLFW doesn't have this.
	g_MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
	g_MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
	g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR); // FIXME: GLFW doesn't have this.
	g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR); // FIXME: GLFW doesn't have this.
	g_MouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

	if (install_callbacks)
	{
		glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
		glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
		glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
		glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
	}

	g_ClientApi = client_api;
	return true;
}

void ImGui_ImplGlfw_Shutdown()
{
	// Destroy GLFW mouse cursors
	for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
		glfwDestroyCursor(g_MouseCursors[cursor_n]);
	// Reset variables
	memset(g_MouseCursors, 0, sizeof(g_MouseCursors));
	g_ClientApi = GlfwClientApi_Unknown;
}

void ImGui_ImplGlfw_UpdateMousePosAndButtons()
{
	ImGuiIO& io = ImGui::GetIO();
	// Update mouse buttons
	for (int i = 0; i < IM_ARRAYSIZE(g_MouseJustPressed); i
		{
			io.MouseDown[i] = g_MouseJustPressed[i] || glfwGetMouseButton(g_Window, i) != 0;
			g_MouseJustPressed[i] = false;
		}

		// Update mouse position
	ImVec2 mouse_pos_backup = io.MousePos;
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
		if (glfwGetWindowAttrib(g_Window, GLFW_FOCUSED))
		{
			if (io.WantSetMousePos)
			{
				glfwSetCursorPos(g_Window, (double)mouse_pos_backup.x, (double)mouse_pos_backup.y);
			}
			else
			{
				double mouse_x, mouse_y;
				glfwGetCursorPos(g_Window, &mouse_x, &mouse_y);
				io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
			}
		}
}

void ImGui_ImplGlfw_UpdateMouseCursors()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
		return;
	ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
	GLFWcursor* glfw_cursor = g_MouseCursors[imgui_cursor];
	if (glfw_cursor && imgui_cursor != ImGuiMouseCursor_None)
	{
		glfwSetCursor(g_Window, glfw_cursor);
	}
	else
	{
		glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}

void ImGui_ImplGlfw_UpdateGamepad()
{
	ImGuiIO& io = ImGui::GetIO();
	memset(io.NavInputs, 0, sizeof(io.NavInputs));
	if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
		return;

	// Update gamepad inputs
	// You may manually update the io.NavInputs[] array from your application
	// See ImGui_ImplGlfw_NewFrame() for an example of how to query GLFW gamepad state
}

void ImGui_ImplGlfw_NewFrame()
{
	ImGuiIO& io = ImGui::GetIO();
	IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! Did you call io.Fonts->Build() or ImGui::NewFrame()?");
	// Setup display size
	int w, h;
	int display_w, display_h;
	glfwGetWindowSize(g_Window, &w, &h);
	glfwGetFramebufferSize(g_Window, &display_w, &display_h);
	io.DisplaySize = ImVec2((float)w, (float)h);
	io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

	// Setup time step
	double current_time = glfwGetTime();
	io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
	g_Time = current_time;

	// Update mouse inputs
	ImGui_ImplGlfw_UpdateMousePosAndButtons();

	// Update mouse cursors
	ImGui_ImplGlfw_UpdateMouseCursors();

	// Update gamepad inputs
	ImGui_ImplGlfw_UpdateGamepad();
}
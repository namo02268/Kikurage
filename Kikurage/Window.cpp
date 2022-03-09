#include "Window.h"

Window::Window(int width, int height, const char* title)
	: m_width(width), m_height(height), m_title(title)
{
	Init();
}

Window::~Window() { Terminate(); }

void Window::Clear() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update() {
	this->anyKeyEvent = false;
	this->anyMouseEvent = false;
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::Init() {
	// initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// create GLFW window 
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (m_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		Terminate();
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* w, int width, int height) {
		glViewport(0, 0, width, height);
		Window& window = *(Window*)glfwGetWindowUserPointer(w);
		window.m_width = width;
		window.m_height = height;
		});

	// key input
	glfwSetKeyCallback(m_window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_REPEAT) return;

			Window& window = *(Window*)glfwGetWindowUserPointer(w);
			if ((size_t)key >= 350) return; // TODO: handle all key input
			window.m_keyPressed[(size_t)key] = (action == GLFW_PRESS);
			window.m_keyReleased[(size_t)key] = (action == GLFW_RELEASE);
			window.m_keyHeld[(size_t)key] = (action == GLFW_PRESS);
			window.anyKeyEvent = true;
		});

	// mouse button input
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* w, int button, int action, int mods)
		{
			if (action == GLFW_REPEAT) return;

			Window& window = *(Window*)glfwGetWindowUserPointer(w);
			if (button >= 8) return;
			window.m_mousePressed[(size_t)button] = (action == GLFW_PRESS);
			window.m_mouseReleased[(size_t)button] = (action == GLFW_RELEASE);
			window.m_mouseHeld[(size_t)button] = (action == GLFW_PRESS);
			window.anyMouseEvent = true;
		});

	// mouse scroll
	glfwSetScrollCallback(m_window, [](GLFWwindow* w, double xoffset, double yoffset) {
		Window& window = *(Window*)glfwGetWindowUserPointer(w);
		window.m_mouseScroll = yoffset;
		window.anyMouseEvent = true;
		});

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// OpenGL configuration
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_MULTISAMPLE);
	// enable seamless cubemap sampling for lower mip levels in the pre-filter map.
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void Window::Terminate() {
	glfwTerminate();
}

glm::vec2 Window::GetCursorPosition() const {
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return glm::vec2(float(x), float(y));
}

void Window::disableMouseCursor() const {
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::normalMouseCursor() const {
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
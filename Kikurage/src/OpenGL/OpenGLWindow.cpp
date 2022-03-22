#include "OpenGL/OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(int width, int height, const char* title) {
	m_width = width;
	m_height = height;
	m_title = title;
	Init();
	MakeFBO();
}

OpenGLWindow::~OpenGLWindow() { Terminate(); }

void OpenGLWindow::Clear() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLWindow::Update() {
	this->anyKeyEvent = false;
	this->anyMouseEvent = false;
	glfwGetCursorPos(m_window, &m_cursorPos[0], &m_cursorPos[1]);
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void OpenGLWindow::Init() {
	// initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
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
		OpenGLWindow& window = *(OpenGLWindow*)glfwGetWindowUserPointer(w);
		window.m_width = width;
		window.m_height = height;
		});

	// key input
	glfwSetKeyCallback(m_window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_REPEAT) return;

			OpenGLWindow& window = *(OpenGLWindow*)glfwGetWindowUserPointer(w);
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

			OpenGLWindow& window = *(OpenGLWindow*)glfwGetWindowUserPointer(w);
			if (button >= 8) return;
			window.m_mousePressed[(size_t)button] = (action == GLFW_PRESS);
			window.m_mouseReleased[(size_t)button] = (action == GLFW_RELEASE);
			window.m_mouseHeld[(size_t)button] = (action == GLFW_PRESS);
			window.anyMouseEvent = true;
		});

	// mouse scroll
	glfwSetScrollCallback(m_window, [](GLFWwindow* w, double xoffset, double yoffset) {
		OpenGLWindow& window = *(OpenGLWindow*)glfwGetWindowUserPointer(w);
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

void OpenGLWindow::Terminate() {
	glfwTerminate();
}

void OpenGLWindow::MakeFBO() {
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLWindow::disableMouseCursor() const {
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void OpenGLWindow::normalMouseCursor() const {
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
#include "OpenGL/OpenGLWindow.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"
#include "Kikurage/Events/WindowResizeEvent.h"

namespace Kikurage {
	OpenGLWindow::OpenGLWindow(int width, int height, const char* title) {
		m_width = width;
		m_height = height;
		m_title = title;
		Init();

		float renderVertices[] = {
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		// screen quad VAO
		glGenVertexArrays(1, &renderVAO);
		glGenBuffers(1, &renderVBO);
		glBindVertexArray(renderVAO);
		glBindBuffer(GL_ARRAY_BUFFER, renderVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(renderVertices), &renderVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		ResourceManager::GetInstance().LoadShaderFromFile("resources/shaders/screen.vert", "resources/shaders/screen.frag", nullptr, "screen");
		screenShader = ResourceManager::GetInstance().GetShader("screen");
		screenShader->Bind();
		screenShader->SetUniform("screenTexture", 0);
	}

	OpenGLWindow::~OpenGLWindow() { Terminate(); }

	void OpenGLWindow::Draw() {
		screenShader->Bind();
		glBindVertexArray(renderVAO);
		glBindTexture(GL_TEXTURE_2D, Application::GetInstance().GetRenderer()->GetRenderTexture().GetHandle());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void OpenGLWindow::Clear() {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLWindow::Update() {
		this->anyKeyEvent = false;
		this->anyMouseEvent = false;
		this->m_mousePressed.reset();
		this->m_keyPressed.reset();

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

		// framebuffer size
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* w, int width, int height) {
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
			window.m_mouseScroll = static_cast<float>(yoffset);
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
		glfwSwapInterval(1);

		// enable seamless cubemap sampling for lower mip levels in the pre-filter map.
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void OpenGLWindow::Terminate() {
		glfwTerminate();
	}

	void OpenGLWindow::disableMouseCursor() const {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void OpenGLWindow::normalMouseCursor() const {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void OpenGLWindow::SetCursorPos(const float xpos, const float ypos) {
		glfwSetCursorPos(m_window, xpos, ypos);
	}
}

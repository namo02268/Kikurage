#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "ResourceManager.h"

// GLFW Callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	//--------------------------------------initialize--------------------------------------//
// initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// create GLFW window 
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Haptas", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);


	ResourceManager::LoadShaderFromFile("resources/shaders/light_cube.vert", "resources/shaders/light_cube.frag", nullptr, "light_cube");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");	

	//--------------------------------------render loop--------------------------------------//
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		if (deltaTime >= 1.0f / 60.0f) {
			lastFrame = currentFrame;

			// input
			processInput(window);

			// render
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// swap buffers and poll events
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;

	/*
	auto entityManager = std::make_unique<EntityManager>();
	Scene scene(std::move(entityManager));

	auto colliderSystem = std::make_unique<ColliderSystem>();
	scene.addSystem(std::move(colliderSystem));

	auto player = scene.createEntity();
	auto enemy = scene.createEntity();

	scene.addComponent<RendererComponent>(player);
	scene.addComponent<TransformComponent>(player, 10.0f, 10.0f);

	scene.addComponent<RendererComponent>(enemy);
	scene.addComponent<ColliderComponent>(enemy);
	scene.addComponent<TransformComponent>(enemy, 20.0f, 20.0f);

	scene.init();
	scene.update();
	scene.draw();
	*/
}

//--------------------------------------GLFW Callback--------------------------------------//
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

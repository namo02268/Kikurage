#pragma once

class Application {
public:
	Application(int width = 1200, int height = 800, const char* title = "Kikurage");
	~Application();
	void Run();
};


Application::Application(int width, int height, const char* title) {
}

Application::~Application() {
}

void Application::Run() {
}
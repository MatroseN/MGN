#include "core/Window.h"
#include "core/Input.h"
#include "renderer/Shader.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace MGN;

const int windowWidth = 1280;
const int windowHeight = 720;
const char* windowTitle = "MGN";

static Shader shader;

int exitWithError(const char* msg){
	printf(msg);
	glfwTerminate();
	return -1;
}

int main(){
	glfwInit();

	Window* window = Window::createWindow(windowWidth, windowHeight, windowTitle);
	if (window == nullptr){
		return exitWithError("Failed to create GLFW window\n");
	}

	window->installMainCallbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		return exitWithError("Failed to initialize GLAD.\n");
	}

	Window::centerWindow(window->nativeWindow);

	// Make sure not to call any OpenGL functions until *after* we initialize our function loader
	shader.compile();

	glViewport(0, 0, windowWidth, windowHeight);
	shader.bind();
	while (!glfwWindowShouldClose(window->nativeWindow)){
		glClearColor(0.266f, 0.466f, 0.698f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (Input::isKeyDown(GLFW_KEY_ESCAPE)){
			Window::freeWindow(window);
			glfwTerminate();
			return 0;
		}

		glfwSwapBuffers(window->nativeWindow);
		glfwPollEvents();
	}

	Window::freeWindow(window);
	glfwTerminate();
	return 0;
}
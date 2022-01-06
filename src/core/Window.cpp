#include "core/Window.h"
#include "core/Input.h"

namespace MGN {
    void Window::installMainCallbacks(){
        if(nativeWindow != nullptr){
            glfwSetKeyCallback(nativeWindow, Input::keyCallback);
			glfwSetCursorPosCallback(nativeWindow, Input::mouseCallback);
			glfwSetMouseButtonCallback(nativeWindow, Input::mouseButtonCallback);
        }
    }

    void Window::close(){
        if(nativeWindow != nullptr){
            glfwSetWindowShouldClose(nativeWindow, GLFW_TRUE);
        }
    }

    Window* Window::createWindow(int width, int height, const char* title, bool fullScreenMode){
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Only supply the monitor if we want to start the window in full-screen mode
		Window* res = new Window();
		GLFWmonitor* primaryMonitor = fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
		res->nativeWindow = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
		if (res->nativeWindow == nullptr){
			printf("Failed to create GLFW window\n");
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(res->nativeWindow);

		return res;
    }

    void Window::freeWindow(Window* window){
        if(window){
            glfwDestroyWindow(window->nativeWindow);
            delete window;
        }
    }

    void Window::centerWindow(GLFWwindow* window){
    // Get window position and size
    int window_x, window_y;
    glfwGetWindowPos(window, &window_x, &window_y);

    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    // Halve the window size and use it to adjust the window position to the center of the window
    window_width *= 0.5;
    window_height *= 0.5;

    window_x += window_width;
    window_y += window_height;

    // Get the list of monitors
    int monitors_length;
    GLFWmonitor **monitors = glfwGetMonitors(&monitors_length);

    if(monitors == NULL) {
        // Got no monitors back
        return;
    }

    // Figure out which monitor the window is in
    GLFWmonitor *owner = NULL;
    int owner_x, owner_y, owner_width, owner_height;

    for(int i = 0; i < monitors_length; i++) {
        // Get the monitor position
        int monitor_x, monitor_y;
        glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

        // Get the monitor size from its video mode
        int monitor_width, monitor_height;
        GLFWvidmode *monitor_vidmode = (GLFWvidmode*) glfwGetVideoMode(monitors[i]);

        if(monitor_vidmode == NULL) {
            // Video mode is required for width and height, so skip this monitor
            continue;

        } else {
            monitor_width = monitor_vidmode->width;
            monitor_height = monitor_vidmode->height;
        }

        // Set the owner to this monitor if the center of the window is within its bounding box
        if((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
            owner = monitors[i];

            owner_x = monitor_x;
            owner_y = monitor_y;

            owner_width = monitor_width;
            owner_height = monitor_height;
        }
    }

    if(owner != NULL) {
        // Set the window position to the center of the owner monitor
        glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
    }
}

}
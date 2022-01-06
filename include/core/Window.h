#pragma once

#include "core.h"

namespace MGN {
	struct Window {
		GLFWwindow* nativeWindow;
		int windowWidth;
		int windowHeight;

		void installMainCallbacks();

		void close();
	
		static Window* createWindow(int width, int height, const char* title, bool fullScreenMode=false);
		static void freeWindow(Window* window);
		static void centerWindow(GLFWwindow* window);
	};
}
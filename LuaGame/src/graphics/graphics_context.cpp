#include "graphics_context.h"
#include "../common.h"

using namespace luagame;

luagame::graphics_context::graphics_context(int width, int height, const char * title) {
	if (!glfwInit())
		_err("failed to initialize");
	else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LG_OPENGL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LG_OPENGL_VERSION_MINOR);
		glfwWindowHint(GLFW_FOCUSED, true);

		glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

		glfwMakeContextCurrent(glfw_window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!glfw_window) {
			_err("failed to create window");
			glfwTerminate();
		}

		glEnable(GL_DEPTH_TEST);

		_log("initialized glfw context");
	}
}

luagame::graphics_context::~graphics_context() {
	if (scene) {
		if (!scene->release()) _err("graphics context did not hold last reference to scene");
	}

	glfwTerminate();

	_log("terminated glfw");
}

luagame::scene_manager * luagame::graphics_context::get_scene() {
	if (!scene) scene = new scene_manager();
	return scene;
}

void luagame::graphics_context::poll_events() {
	glfwPollEvents();
}

void luagame::graphics_context::swap_buffers() {
	glfwSwapBuffers(glfw_window);
}

void luagame::graphics_context::set_title(const char * new_title) {
	glfwSetWindowTitle(glfw_window, new_title);
	_log("set window title to: %s", new_title);
}

bool luagame::graphics_context::get_should_close() {
	return glfwWindowShouldClose(glfw_window) == GLFW_TRUE;
}

void luagame::graphics_context::set_should_close(bool should_close) {
	glfwSetWindowShouldClose(glfw_window, should_close);
}
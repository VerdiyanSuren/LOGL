#ifndef VFLOGL_APP_H
#define VFLOGL_APP_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace vfLOGL
{
	class App
	{
	public:
		static App& app();
		void run();
	private:
		App();
	private:
		static App* g_app;
		static bool g_glfw_initialized;
	private:
		// callsbacks
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void resize(GLFWwindow* window, int width, int height);
	public:
		static int g_width, g_height;
		static std::string g_title;
		static GLFWwindow* g_wnd;
	};
}

#endif //!VFLOGL_APP_H
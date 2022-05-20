#ifndef VFLOGL_APP_H
#define VFLOGL_APP_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace vfLOGL
{
	class vfLOGLApp
	{
	public:
		static vfLOGLApp& app();
		void run();
	private:
		vfLOGLApp();
	private:
		static vfLOGLApp* g_app;
		static bool g_glfw_initialized;
		static void resize(GLFWwindow* window, int width, int height);
	public:
		static int g_width, g_height;
		static std::string g_title;
		static GLFWwindow* g_wnd;
	};
}

#endif //!VFLOGL_APP_H
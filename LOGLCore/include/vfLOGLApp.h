#ifndef VFLOGL_APP_H
#define VFLOGL_APP_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shaders/vfShaderLib.h>
#include <vfCamera.h>
#include <string>

namespace vfLOGL
{
	class App
	{
	public:
		enum class CameraTrackMode
		{
			k_none,
			k_rotate,
			k_pan,
			k_dolly
		};
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
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void resize(GLFWwindow* window, int width, int height);
	public:
		static int g_width, g_height;
		static std::string g_title;
		static GLFWwindow* g_wnd;
		static ShaderLib   g_shader_lib;
		static Camera*	g_camera;
		static bool		g_keys[1024];
		static CameraTrackMode g_mouse_mode;
		static float g_cam_press_x, g_cam_press_y;
	};
}

#endif //!VFLOGL_APP_H
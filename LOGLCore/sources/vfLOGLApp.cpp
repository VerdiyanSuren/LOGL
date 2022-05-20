#include <vfLOGLApp.h>
#include <iostream>
using namespace vfLOGL;

vfLOGLApp* vfLOGLApp::g_app			= nullptr;
bool vfLOGLApp::g_glfw_initialized	= false;
int vfLOGLApp::g_width				= 800;
int vfLOGLApp::g_height				= 600;
std::string vfLOGLApp::g_title		= "Test Window";
GLFWwindow* vfLOGLApp::g_wnd		= nullptr;

#pragma region DefaultCallbacks
void vfLOGLApp::resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
#pragma endregion

vfLOGLApp& vfLOGLApp::app()
{
	if (g_app == nullptr)	g_app = new vfLOGLApp();
	return *g_app;
}
vfLOGLApp::vfLOGLApp()
{
	if (g_glfw_initialized == false) {
		if (!glfwInit())
		{
			std::cout << ":> glfwInit error" << std::endl;
			g_glfw_initialized = false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		g_wnd = glfwCreateWindow(g_width, g_height, g_title.c_str(), nullptr, nullptr);
		if (g_wnd == nullptr)
		{
			std::cout << ":> Failed to create window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwSwapInterval(1);
		glfwMakeContextCurrent(g_wnd);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << ":>Failed to initialize GLAD" << std::endl;
			return;
		}
		int width, height;
		glfwGetFramebufferSize(g_wnd, &width, &height);
		glViewport(0, 0, width, height);
		//glViewport(0, 0, 800, 600);
		std::cout << "viewport size " << width << " " << height << std::endl;

		// set callbacks
		glfwSetFramebufferSizeCallback(g_wnd, resize);


 		g_glfw_initialized = true;

	}
}
void vfLOGLApp::run()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(g_wnd))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		//glfwSwapBuffers(g_wnd);
	}
	glfwTerminate();
}
#include <vfLOGLApp.h>
#include <Geometry/vfMeshLoader.h>
#include <Geometry/vfMesh.h>
#include <iostream>
using namespace vfLOGL;

App* App::g_app					= nullptr;
bool App::g_glfw_initialized	= false;
int App::g_width				= 800;
int App::g_height				= 600;
std::string App::g_title		= "Test Window";
GLFWwindow* App::g_wnd			= nullptr;

#pragma region DefaultCallbacks
void App::resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void App::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}

#pragma endregion

App& App::app()
{
	if (g_app == nullptr)	g_app = new App();
	return *g_app;
}
App::App()
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
		glfwSetKeyCallback(g_wnd, key_callback);

 		g_glfw_initialized = true;

	}
}
void App::run()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(g_wnd))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto& mesh: MeshLoader::m_meshes)
		{
			mesh.bind();
			mesh.draw();
			mesh.unbind();

		}
		glfwSwapBuffers(g_wnd);
	}
	glfwTerminate();
}
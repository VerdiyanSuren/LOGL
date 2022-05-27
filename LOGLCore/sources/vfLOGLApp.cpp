#include <vfLOGLApp.h>
#include <Geometry/vfMeshLoader.h>
#include <Geometry/vfMesh.h>
#include <vfCamera.h>
#include <vfTransform.h>
#include <iostream>
using namespace vfLOGL;

App* App::g_app					= nullptr;
bool App::g_glfw_initialized	= false;
int App::g_width				= 800;
int App::g_height				= 600;
std::string		App::g_title	= "Test Window";
GLFWwindow*		App::g_wnd		= nullptr;
Shader*			App::g_shader	= nullptr;
Camera*			App::g_camera	= nullptr;

bool App::g_keys[1024]			= { false };
App::CameraTrackMode App::g_mouse_mode = App::CameraTrackMode::k_none;
float App::g_cam_press_x, App::g_cam_press_y;

#pragma region DefaultCallbacks
void App::resize(GLFWwindow* window, int width, int height)
{
	g_width = width;
	g_height = height;
	glViewport(0, 0, width, height);
}
void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	g_keys[key] = true;
	if (action == GLFW_RELEASE)
	{
		g_keys[key] = false;
	}

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
void App::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	g_mouse_mode = CameraTrackMode::k_none;
}
void App::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float x_pos = static_cast<float>(xpos);
	float y_pos = static_cast<float>(ypos);
	if (g_keys[GLFW_KEY_LEFT_ALT] == true || g_keys[GLFW_KEY_RIGHT_ALT] == true)
	{
		if (g_mouse_mode == CameraTrackMode::k_none)
		{
			g_cam_press_x = x_pos;
			g_cam_press_y = y_pos;
			//cam_mat = g_camera->get_transform().get_xform();
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			// rotate around
			if (g_mouse_mode == CameraTrackMode::k_none)
			{
				g_mouse_mode = CameraTrackMode::k_rotate;
			}
			if (g_mouse_mode == CameraTrackMode::k_rotate)
			{
				float dx = g_cam_press_x - x_pos; dx *= 360.0f / float(g_width);
				float dy = g_cam_press_y - y_pos; dy *= 180.0f / float(g_height);
				// horizontal rotation around world axis y
				glm::mat4 l_xmat = glm::mat4(glm::angleAxis(glm::radians(dx), glm::vec3(0.0f, 1.0f, 0.0f)));
				g_camera->get_transform().rotate_around(l_xmat);

				// vertical rotation
				glm::vec3 cam_z = g_camera->get_transform().get_axis_z();
				glm::vec3 axis_y = glm::vec3(0.0f, 1.0f, 0.0f);
				float angle = glm::degrees(glm::acos(glm::dot(cam_z, axis_y)));
				//if (angle + dy < 2.0f)
				//{
				glm::vec3 l_axis = glm::normalize(glm::cross(axis_y, cam_z));
				glm::mat4 l_ymat = glm::mat4(glm::angleAxis(glm::radians(dy), l_axis));
				g_camera->get_transform().rotate_around(l_ymat);
				//std::cout << "rotate y " << dy << std::endl;
			//}
				g_cam_press_x = x_pos;
				g_cam_press_y = y_pos;
				return;
			}
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			// pan
			if (g_mouse_mode == CameraTrackMode::k_none)
			{				
				g_mouse_mode = CameraTrackMode::k_pan;
			}
			if (g_mouse_mode == CameraTrackMode::k_pan)
			{
				float dx = g_cam_press_x - x_pos; dx *= 0.005f;
				float dy = y_pos - g_cam_press_y; dy *= 0.005f;
				
				glm::vec3 x_axis = g_camera->get_transform().get_axis_x();
				glm::vec3 y_axis = g_camera->get_transform().get_axis_y();
				glm::vec3 offset = x_axis * dx + y_axis * dy;
				
				g_camera->get_transform().add_translate(offset);
				
			
				g_cam_press_x = x_pos;
				g_cam_press_y = y_pos;
				return;
			}
			return;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			// dolly
			if (g_mouse_mode == CameraTrackMode::k_none)
			{
				g_mouse_mode = CameraTrackMode::k_dolly;
			}
			if (g_mouse_mode == CameraTrackMode::k_dolly)
			{
				float dx = g_cam_press_x - x_pos; dx *= 0.005f;
				float dy = y_pos - g_cam_press_y; dy *= 0.005f;

				glm::vec3 z_axis = g_camera->get_transform().get_axis_z();				
				glm::vec3 offset = z_axis * (dx + dy);

				g_camera->get_transform().add_translate(offset);

				g_cam_press_x = x_pos;
				g_cam_press_y = y_pos;
				return;
			}
			return;
		}
	}
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
		glfwSetCursorPosCallback(g_wnd, mouse_callback);
		glfwSetMouseButtonCallback(g_wnd, mouse_button_callback);

		g_shader = new Shader("basic.shader");

		g_camera = new Camera();
		g_camera->get_transform().set_translate(glm::vec3(0.0f, 0.0f, 3.0f));
		g_camera->set_fov(45);

 		g_glfw_initialized = true;

		glEnable(GL_DEPTH_TEST);
	}
}
void App::run()
{
	g_shader->use();
	g_shader->set_int("u_dlCount", 1);
	g_shader->set_vec3("u_ambient", glm::vec3(0.1f, 0.2f, 0.3f));
	GLint mvp = glGetUniformLocation(g_shader->get_id(), "u_MVP");
	std::cout << "u_MVP " << mvp << std::endl;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(g_wnd))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		g_shader->use();
		g_shader->set_matrix("u_MVP", g_camera->get_vp());
		//glUniformMatrix4fv(glGetUniformLocation(g_shader->get_id(), "u_MVP"), 1, GL_FALSE, &(g_camera->get_vp()[0][0]));
		//glUniformMatrix4fv(glGetUniformLocation(g_shader->get_id(), "u_MVP"), 1, GL_FALSE, &mat[0][0]);
		for (auto& mesh: MeshLoader::m_meshes)
		{
			mesh.bind();
			mesh.draw();
		}
		glfwSwapBuffers(g_wnd);
	}
	g_shader->release();
	delete g_shader;
	delete g_camera;
	glfwTerminate();
}
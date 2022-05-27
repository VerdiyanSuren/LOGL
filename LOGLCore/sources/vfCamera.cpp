#include <vfCamera.h>
#include <vfLOGLApp.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace vfLOGL;

Camera::Camera()
{
	compute_proj();
}
void Camera::set_fov(float val)
{
	m_fov = val; 
}
void Camera::set_near(float val)
{
	m_near = val;
}
void Camera::set_far(float val)
{
	m_far = val;
}
void Camera::set_transform(const Transform& val)
{
	m_transform = val;
}
void Camera::compute_proj()
{
	if (m_ortho == false){ 
		m_proj = glm::perspective(glm::radians(m_fov), float(App::g_width)/float(App::g_height), m_near, m_far);
		m_vp = m_proj * glm::inverse(m_transform.xform());
		return;
	}
	m_proj = glm::ortho( -float(App::g_width)/2.0f,float(App::g_width)/2.0f, -float(App::g_height)/2.0f, float(App::g_height), m_near, m_far);
	m_vp = m_proj * glm::inverse(m_transform.xform());
}
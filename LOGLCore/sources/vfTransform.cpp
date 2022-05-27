#include <vfTransform.h>
#include<glm/common.hpp>

using namespace vfLOGL;


glm::vec3 Transform::get_axis_x() const
{
	return glm::vec3(m_xform[0][0], m_xform[0][1], m_xform[0][2]);
}
glm::vec3 Transform::get_axis_y() const
{
	return glm::vec3(m_xform[1][0], m_xform[1][1], m_xform[1][2]);
}
glm::vec3 Transform::get_axis_z() const
{
	return glm::vec3(m_xform[2][0], m_xform[2][1], m_xform[2][2]);
}


void Transform::set_translate(const glm::vec3& pos)
{
	m_xform[3][0] = pos.x;
	m_xform[3][1] = pos.y;
	m_xform[3][2] = pos.z;
}
void Transform::set_translate(float x, float y, float z)
{
	m_xform[3][0] = x;
	m_xform[3][1] = y;
	m_xform[3][2] = z;
}
void Transform::add_translate(const glm::vec3& offset)
{
	m_xform[3][0] += offset.x;
	m_xform[3][1] += offset.y;
	m_xform[3][2] += offset.z;
}
void Transform::add_translate(float x, float y, float z)
{
	m_xform[3][0] += x;
	m_xform[3][1] += y;
	m_xform[3][2] += z;
}
void Transform::set_rotation(const glm::quat& q)
{
	glm::mat3 res =  glm::mat3_cast(q);
	//glm::mat3 rotate_origin  = glm::mat3(m_xform);
	//glm::mat3 res = rotate_matrix* rotate_origin;
	
	m_xform[0][0] = res[0][0];
	m_xform[0][1] = res[0][1];
	m_xform[0][2] = res[0][2];

	m_xform[1][0] = res[1][0];
	m_xform[1][1] = res[1][1];
	m_xform[1][2] = res[1][2];

	m_xform[2][0] = res[2][0];
	m_xform[2][1] = res[2][1];
	m_xform[2][2] = res[2][2];
}
void Transform::set_rotation(float angle, const glm::vec3& axis)
{
	glm::quat q = glm::angleAxis(glm::radians(angle), axis);
	set_rotation(q);
}
void Transform::set_rotation(float x, float y, float z)
{
	glm::mat3 rx = glm::mat3_cast(glm::angleAxis(glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f)));
	glm::mat3 ry = glm::mat3_cast(glm::angleAxis(glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::mat3 rz = glm::mat3_cast(glm::angleAxis(glm::radians(x), glm::vec3(0.0f, 0.0f, 1.0f)));

	glm::mat3 res = rz* ry* rx;

	m_xform[0][0] = res[0][0];
	m_xform[0][1] = res[0][1];
	m_xform[0][2] = res[0][2];

	m_xform[1][0] = res[1][0];
	m_xform[1][1] = res[1][1];
	m_xform[1][2] = res[1][2];

	m_xform[2][0] = res[2][0];
	m_xform[2][1] = res[2][1];
	m_xform[2][2] = res[2][2];	
}
void Transform::set_rotation(const glm::mat3& rot)
{
	m_xform[0][0] = rot[0][0];
	m_xform[0][1] = rot[0][1];
	m_xform[0][2] = rot[0][2];

	m_xform[1][0] = rot[1][0];
	m_xform[1][1] = rot[1][1];
	m_xform[1][2] = rot[1][2];

	m_xform[2][0] = rot[2][0];
	m_xform[2][1] = rot[2][1];
	m_xform[2][2] = rot[2][2];
}
void Transform::rotate_around(const glm::mat4& rot)
{
	/*
	glm::mat4 origin = rot;
	origin[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	origin[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	origin[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	
	origin[3][0] = -origin[3][0];
	origin[3][1] = -origin[3][1];
	origin[3][2] = -origin[3][2];
	*/
	
	//m_xform = rot* (origin * m_xform);
	m_xform = rot * m_xform;
}
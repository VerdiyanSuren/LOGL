#include <vfUniformBufferObject.h>
#include <glad/glad.h>
#include <iostream>
using namespace vfLOGL;

UniformBufferObject::UniformBufferObject()
{}
void UniformBufferObject::realloc(unsigned int bind_point, unsigned int p_size)
{
	if (p_size == m_buff_size)	return;
	if (m_id != 0)				free();

	glGenBuffers(1, &m_id);
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	glBufferData(GL_UNIFORM_BUFFER, p_size, nullptr, GL_STATIC_DRAW);
	//glBindBufferRange(GL_UNIFORM_BUFFER, bind_point, m_id, 0, m_buff_size);
	glBindBufferBase(GL_UNIFORM_BUFFER, bind_point, m_id);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	m_buff_size = p_size;
}
void UniformBufferObject::free()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glDeleteBuffers(1, &m_id);
	m_id		= 0;
	m_buff_size = 0;
}
void UniformBufferObject::bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}
void UniformBufferObject::unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
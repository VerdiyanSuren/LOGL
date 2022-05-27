#include <vfUniformBufferObject.h>
#include <glad/glad.h>

using namespace vfLOGL;

UniformBufferObject::UniformBufferObject(unsigned int p_size) :m_buff_size(p_size)
{}
void UniformBufferObject::allocate(unsigned int bind_point)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	glBufferData(GL_UNIFORM_BUFFER, m_buff_size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	glBindBufferRange(GL_UNIFORM_BUFFER, bind_point, m_id, 0, m_buff_size);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void UniformBufferObject::free()

{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glDeleteBuffers(1, &m_id);
}
void UniformBufferObject::bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}
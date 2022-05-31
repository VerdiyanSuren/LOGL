#include <vfFrameBufferObject.h>
#include <glad/glad.h>
#include <iostream>

using namespace vfLOGL;


void FrameBufferObject::realloc(unsigned int bind_point, unsigned int p_size)
{	
	if (m_id != 0)				free();

	glGenFramebuffers(1, &m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_buff_size = p_size;
}
void FrameBufferObject::free()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &m_id);
	m_id = 0;
}

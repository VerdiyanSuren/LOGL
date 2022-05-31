#include <Texture/vfTexture2d.h>
#include <glad/glad.h>
#include <SOIL/SOIL.h>

using namespace vfLOGL;

Texture2D::Texture2D(const std::string& file_path)
{
	unsigned char* image = SOIL_load_image(file_path.c_str(), &m_width, &m_height,&m_channels, SOIL_LOAD_AUTO);
	if (!image)		return;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	SOIL_free_image_data(image);
}
void Texture2D::bind(GLenum slot)
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}
#include <glad/glad.h>
#include <vfDirectLight.h>
#include <Shaders/vfShader.h>
#include <vfLOGLApp.h>
#include <iostream>
using namespace vfLOGL;

static const std::string	g_ubo_name =			LOGL_DIRECT_LIGHT_NAME;
const unsigned int									DirectLight::g_bind_point = 6;
unsigned int										DirectLight::g_light_count = 0;
UniformBufferObject									DirectLight::g_ubo;
std::array<DirectLight::Light, LOGL_DIRECT_LIGHT_SIZE>	DirectLight::g_dlights;


unsigned int DirectLight::get_size()
{
	return (sizeof(GLuint) + g_light_count * sizeof(DirectLight::Light) );
}
DirectLight::Light* DirectLight::create_light()
{	
	if (g_light_count >= LOGL_DIRECT_LIGHT_SIZE)
	{
		return nullptr;
	}	
	return &g_dlights[g_light_count++];
}
DirectLight::Light* DirectLight::get_light(unsigned int ndx)
{
	return ndx <= g_light_count? &g_dlights[ndx]:nullptr;
}
void DirectLight::clear_all_lights()
{	
	g_light_count = 0;
	g_ubo.free();
}
void DirectLight::update_ubo()
{	
	g_ubo.realloc(g_bind_point, sizeof(GLuint) + LOGL_DIRECT_LIGHT_SIZE * sizeof(DirectLight::Light)  + 3 * sizeof(GLfloat)  );
	if (g_light_count > 0)
	{
		g_ubo.bind();
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLuint), (GLvoid*)&g_light_count);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(GLuint) + 3 * sizeof(GLfloat), LOGL_DIRECT_LIGHT_SIZE * sizeof(DirectLight::Light), (GLvoid*)&g_dlights[0]);
		g_ubo.unbind();
		auto& shLib = App::g_shader_lib;
		for (unsigned int i = 0; i < shLib.size(); ++i)
		{
			auto shader_id = shLib.get(i)->get_id();
			unsigned int uniform_ndx = glGetUniformBlockIndex(shader_id, LOGL_DIRECT_LIGHT_NAME);
			glUniformBlockBinding(shader_id, uniform_ndx, g_bind_point);
		}
	}
}
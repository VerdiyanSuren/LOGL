#ifndef VF_LOGL_DIRECT_LIGHT_H
#define VF_LOGL_DIRECT_LIGHT_H

#include <glm/glm.hpp>
#include <vfUniformBufferObject.h>
#include <array>
#include <string>
#define LOGL_DIRECT_LIGHT_SIZE 4
#define LOGL_DIRECT_LIGHT_NAME "DirectLight"
namespace vfLOGL
{	
	class DirectLight
	{
	public:
		struct Light
		{
			//float pass_1;
			//float pass_2;
			//float pass_3;
			glm::vec4 direction = glm::normalize(glm::vec4(-1.0f, -2.0f, 0.0f, 0));
			glm::vec4 diffuse	= glm::vec4(1.0f, 1.0f, 1.0f, 0);
			glm::vec4 specular	= glm::vec4(0.0f, 0.0f, 1.0f, 0);
			float intensity = 0.2f;
			//float attenuation = 0.2f;
			float pass_1;
			float pass_2;
			float pass_3;
		};
	private:
		DirectLight() {}
	public:
		static unsigned int get_size();
		static Light* create_light();
		static Light* get_light(unsigned int ndx);
		static void			clear_all_lights();
		static void			update_ubo();
	private:
		static const std::string	g_ubo_name;
		static const unsigned int	g_bind_point;
		static unsigned int			g_light_count;
		static UniformBufferObject	g_ubo;

		static std::array<Light ,LOGL_DIRECT_LIGHT_SIZE> g_dlights;
		
	};
}

#endif !//VF_LOGL_DIRECT_LIGHT_H
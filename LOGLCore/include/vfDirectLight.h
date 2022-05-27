#ifndef VF_LOGL_DIRECT_LIGHT_H
#define VF_LOGL_DIRECT_LIGHT_H

#include <glm/glm.hpp>

namespace vfLOGL
{
	class DirectLight
	{
	public:
		glm::vec3 direction = glm::normalize(glm::vec3(-1,-1,0));
		glm::vec3 diffuse	= glm::vec3(1, 1, 1);
		glm::vec3 specular	= glm::vec3(1, 1, 1);
		float intensity = 1.0;
		float attenuation = 0;
	};
}

#endif !//VF_LOGL_DIRECT_LIGHT_H
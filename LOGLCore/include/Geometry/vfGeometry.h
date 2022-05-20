#ifndef VF_LOGL_GEOMETRY_H
#define VF_LOGL_GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace vfLOGL
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 norm;
		glm::vec2 uv;
	};
	class Geometry
	{
	public:
		virtual ~Geometry() {}
		//virtual bool load(const char*) = 0;
		virtual void bind()		const = 0;
		virtual void unbind()	const = 0;
		virtual void draw()		const = 0;
	};
}
#endif //!VF_LOGL_GEOMETRY_H
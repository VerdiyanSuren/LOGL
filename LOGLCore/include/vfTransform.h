#ifndef VF_LOGL_TRANSFORM_H
#define VF_LOGL_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace vfLOGL
{
	class Transform
	{
	public:
		glm::vec3 get_axis_x() const;
		glm::vec3 get_axis_y() const;
		glm::vec3 get_axis_z() const;

		void set_translate(const glm::vec3& pos);
		void set_translate(float x, float y, float z);
		void add_translate(const glm::vec3& offset);
		void add_translate(float x, float y, float z);

		void set_rotation(const glm::quat&);
		void set_rotation(float angle, const glm::vec3& axis);
		void set_rotation(float x, float y, float z);
		void set_rotation(const glm::mat3& rot);
		void rotate_around(const glm::mat4& rot);/*mat3 is rotation, around pos*/
		//void set_scale(float x, float y, float z);
		
		inline glm::mat4& xform() { return m_xform; }
		inline void set_xform(const glm::mat4& mat) { m_xform = mat; }
	private:
		glm::mat4 m_xform = glm::mat4(1.0f);
	};
}

#endif // !VF_LOGL_TRANSFORM_H

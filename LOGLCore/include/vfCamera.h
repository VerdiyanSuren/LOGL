#ifndef VF_LOGL_CAMERA_H
#define VF_LOGL_CAMERA_H

#include <vfTransform.h>

namespace vfLOGL
{
	class Camera
	{
	public:
		Camera();
		inline float get_fov() const  { return m_fov; }
		inline float get_near() const { return m_near;}
		inline float get_far() const  { return m_far; }
		inline bool  is_ortho() const { return m_ortho; }
		Transform& get_transform() { return m_transform; }
		glm::mat4& get_proj() { return m_proj; }
		glm::mat4& get_vp() { compute_proj(); return m_vp; }

		void set_fov(float val);
		void set_near(float val);
		void set_far(float val);
		void set_transform(const Transform& val);

	private:
		bool m_ortho = false;
		void compute_proj();
		Transform m_transform;
		float m_fov = 45.0f;
		float m_near = 0.1f;
		float m_far = 100.0f;
		glm::mat4 m_proj;
		glm::mat4 m_vp;

	};
}

#endif
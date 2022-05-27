#ifndef VF_LOGL_MESH_H
#define VF_LOGL_MESH_H
#include <glad/glad.h>
#include <Geometry/vfGeometry.h>
#include <vfTransform.h>
#include <vector>
namespace vfLOGL
{
	class Mesh:public Geometry
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		virtual ~Mesh() {}
		virtual void bind()		const override;
		virtual void unbind()	const override;
		virtual void draw()		const override;
		virtual void release()	const override;
		virtual Transform& transform() override { return m_transform; }

	private:
		unsigned int m_vao, m_vbo, m_ebo;
		GLsizei m_index_size = 0;
		Transform m_transform;
	};
}
#endif // !VF_LOGL_MESH_H
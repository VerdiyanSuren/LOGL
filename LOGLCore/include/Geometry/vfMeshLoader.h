#ifndef VF_LOGL_MESH_LOADER_H
#define VF_LOGL_MESH_LOADER_H

#include <vector>
/*
namespace Assimp
{
	void aiAssertViolation(const char* failedExpression, const char* file, int line);
	const char* aiTextureTypeToString(enum aiTextureType in);
}
*/
namespace vfLOGL
{
	class Mesh;
	class MeshLoader
	{
	public:
		static Mesh* get_from_file(const char* path);
	public:
		static std::vector<Mesh> m_meshes;
	};
}

#endif //!VF_LOGL_MESH_LOADER_H
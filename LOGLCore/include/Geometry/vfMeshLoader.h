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
		struct MeshInfo
		{
			int m_start_mesh_index = -1;
			int m_loaded_count = 0;
		};
		static MeshInfo get_from_file(const char* path);
		static Mesh& mesh(int ndx);
		static size_t mesh_count();
	public:
		static std::vector<Mesh> m_meshes;
	};
}

#endif //!VF_LOGL_MESH_LOADER_H
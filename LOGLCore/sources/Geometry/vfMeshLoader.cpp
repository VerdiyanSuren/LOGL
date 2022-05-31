#include <Geometry/vfMeshLoader.h>
#include <Geometry/vfMesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>
using namespace vfLOGL;
namespace Assimp
{
	void aiAssertViolation(const char* failedExpression, const char* file, int line)
	{
		std::cout << "aiAssertViolation:> " << failedExpression << " " << file << line << std::endl;
	}
}

std::vector<Mesh> MeshLoader::m_meshes;
Mesh& MeshLoader::mesh(int ndx)
{
	return m_meshes[ndx];
}
size_t MeshLoader::mesh_count()
{
	return m_meshes.size();
}

MeshLoader::MeshInfo MeshLoader::get_from_file(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_FixInfacingNormals);
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
	{
		std::cout << ":>Failed to read mesh " << path <<  std::endl;
		return { -1,0 };
	}
	std::cout << "Root node name: " << scene->mRootNode->mName.C_Str() << std::endl;
	std::cout << "number of nodes " << scene->mRootNode->mNumChildren << std::endl;
	int res_ndx = (int)m_meshes.size();
	int res_cnt = 0;
	for (int i = 0; i < scene->mRootNode->mNumChildren; ++i)
	{
		aiNode* child = scene->mRootNode->mChildren[i];
		if (child->mNumMeshes > 0)
		{
			std::cout << "	child node name: " << child->mName.C_Str() << " num meshes " << child->mNumMeshes << std::endl;
			auto xform = child->mTransformation;
			
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			unsigned int mesh_ndx = child->mMeshes[0];
			aiMesh* mesh = scene->mMeshes[mesh_ndx];
			// read vertices
			vertices.resize(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
			{
				Vertex vertex;
				glm::vec3 vector;
				// position
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.pos = vector;
				// normals
				if (mesh->HasNormals())
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
					vertex.norm = vector;
				}
				else
				{
					std::cout << "mesh has not any normals" << std::endl;
				}
				if (mesh->HasTextureCoords(0))
				{
					vertex.uv.x = mesh->mTextureCoords[0][i].x;
					vertex.uv.y = mesh->mTextureCoords[0][i].y;
				}
				else
				{
					vertex.uv = glm::vec2(0.0f, 0.0f);
				}
				vertices[i] = vertex;
			}
			// read indeces
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			Mesh* res_mesh = new Mesh(vertices, indices);
			// transform
			auto m = res_mesh->transform().xform();
			for (int y = 0; y < 4; ++y)
			{
				for (int z = 0; z < 4; ++z)
				{
					m[y][z] = xform[z][y];
				}
			}
			m_meshes.push_back(*res_mesh);
			res_cnt++;
		}
	}
	return { res_ndx, res_cnt };
}

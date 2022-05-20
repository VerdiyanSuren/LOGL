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

Mesh* MeshLoader::get_from_file(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
	{
		std::cout << ":>Failed to read mesh " << path <<  std::endl;
		return nullptr;
	}
	std::cout << "number of meshes " << scene->mNumMeshes << std::endl;
	
	// then do the same for each of its children
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	
	aiMesh* mesh = scene->mMeshes[0];
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
			std::cout << "mesh has not aany normals" << std::endl;
		}
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = vec;
		}
		else
		{
			std::cout << "mesh has not aany uvs" << std::endl;
		}
		vertices[i] = vertex;
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	Mesh* res_mesh = new Mesh(vertices, indices);
	m_meshes.push_back(*res_mesh);
	return  res_mesh;
}

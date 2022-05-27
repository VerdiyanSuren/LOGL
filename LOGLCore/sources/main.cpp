#include <vfLOGLApp.h>
#include <Geometry/vfMeshLoader.h>
#include <Geometry/vfMesh.h>
#include <iostream>

using namespace vfLOGL;
int main()
{
	std::cout << "Hello" << std::endl;
	auto& engn = App::app();
	auto mesh = MeshLoader::get_from_file("../../../../geometry.obj");
	
	//std::cout << " result mesh is " << mesh << std::endl;
	engn.run();
	//system("pause");
}
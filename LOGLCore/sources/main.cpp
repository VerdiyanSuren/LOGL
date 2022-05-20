#include <vfLOGLApp.h>
#include <iostream>

using namespace vfLOGL;
int main()
{
	std::cout << "Hello" << std::endl;
	auto& engn =  vfLOGLApp::app();
	engn.run();
	system("pause");
}
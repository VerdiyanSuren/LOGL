#ifndef VF_LOGL_SHADER_LIB_H
#define VF_LOGL_SHADER_LIB_H

#include <Shaders/vfShader.h>
#include <vfLib.h>
#include <string>

namespace vfLOGL
{
	class ShaderLib :public Lib<Shader>
	{
	public:
		//ShaderLib();
		//~ShaderLib();
		Shader* new_shader(const std::string& file);
	private:
	};
}

#endif //!VF_LOGL_SHADER_LIB_H
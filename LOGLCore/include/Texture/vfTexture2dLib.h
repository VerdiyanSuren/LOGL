#ifndef VF_LOGL_TEXTURE_2D_LIB_H
#define VF_LOGL_TEXTURE_2D_LIB_H

#include <Texture/vfTexture2d.h>
#include <vfLib.h>
#include <string>

namespace vfLOGL
{
	class Texture2DLib :public Lib<Texture2D>
	{
	public:
		Texture2D* new_texture(const std::string& file_path);
		//Texture2D* new_texture(int width, int depth);
		//~ShaderLib();
		
	private:
	};
}
#endif // !VF_LOGL_TEXTURE_2D_LIB_H
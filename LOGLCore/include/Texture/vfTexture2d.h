#ifndef VF_LOGL_TEXTURE_2D_H
#define VF_LOGL_TEXTURE_2D_H

#include <glad/glad.h>
#include <string>

namespace vfLOGL
{
	template<class T>	class Lib;
	class Texture2D
	{
	public:
		Texture2D(const std::string& file);

		void bind(GLenum slot = GL_TEXTURE0);
		inline unsigned int get_id() { return m_id; }
	private:
		std::string m_name		= "";
		std::string m_file_path = "";
		int m_width				= 0;
		int m_height			= 0;
		int m_channels			= 0;
		unsigned int m_id		= 0;

		friend class ShaderLib;
		friend class Lib<Texture2D>;

	};
}

#endif //!VF_LOGL_TEXTURE_2D_H
#ifndef VF_LOGL_SHADER_H
#define VF_LOGL_SHADER_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
namespace vfLOGL
{
	class Shader
	{
	private:
		unsigned int m_id = 0;
		std::string m_file_path = "";
		std::string m_vrtx = "";
		std::string m_frgmnt = "";
	public:
		Shader(const std::string& file);
		Shader(const std::string& vrtx_source, const std::string& frgmnt_source);
		void use()		const;
		void unuse()	const;
		void release();
		inline unsigned int get_id() { return m_id; }

		void set_matrix(const char* name, const glm::mat4&);
		void set_int(const char* name, GLint);
		void set_vec3(const char* name, const glm::vec3&);
	private:
		unsigned  int	create_shader(const std::string& p_vrtx, const std::string& p_frgmnt);
	public:
		static std::vector<unsigned int> g_id_arr;
	};
}


#endif //!VF_LOGL_SHADER_H
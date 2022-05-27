#include <glad/glad.h>
#include <Shaders/vfShader.h>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace vfLOGL;

Shader::Shader(const std::string& file_path)
{
	enum class ShaderType
	{
		k_none		= -1,
		k_vertex	= 0,
		k_fragment	= 1
	};
	std::ifstream fss(file_path);
	if (fss.fail() == true)
	{
		std::cout << ":>Failed to open file " << file_path << std::endl;
		return;
	}
	std::stringstream ss[2];
	std::string line;
	ShaderType l_state = ShaderType::k_none;
	while (getline(fss, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				l_state = ShaderType::k_vertex;
				continue;
			}
			if (line.find("fragment") != std::string::npos)
			{
				l_state = ShaderType::k_fragment;
				continue;
			}
			l_state = ShaderType::k_none;
		}
		if (l_state == ShaderType::k_none)
		{
			continue;
		}
		ss[(int)l_state] << line << std::endl;
	}
	m_id = create_shader(ss[0].str(), ss[1].str());
}
Shader::Shader(const std::string& vrtx_source, const std::string& frgmnt_source)
{
	m_id = create_shader(vrtx_source, frgmnt_source);
}
unsigned  int	Shader::create_shader(const std::string& p_vrtx, const std::string& p_frgmnt)
{
	GLint	l_success;
	GLchar	l_infoLog[512];
	// vertex shader
	const char* vrtx = p_vrtx.c_str();
	GLuint l_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(l_vertex_shader_id, 1, &vrtx, nullptr);
	glCompileShader(l_vertex_shader_id);
	glGetShaderiv(l_vertex_shader_id, GL_COMPILE_STATUS, &l_success);
	if (l_success == GL_FALSE)
	{
		glGetShaderInfoLog(l_vertex_shader_id, 512, NULL, l_infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << l_infoLog << std::endl;
		std::cout << p_vrtx << std::endl;
		glDeleteShader(l_vertex_shader_id);
		return 0;
	}
	// fragment shader
	const char* frgmnt = p_frgmnt.c_str();
	GLuint l_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(l_fragment_shader_id, 1, &frgmnt, nullptr);
	glCompileShader(l_fragment_shader_id);
	glGetShaderiv(l_fragment_shader_id, GL_COMPILE_STATUS, &l_success);
	if (l_success == GL_FALSE)
	{
		glGetShaderInfoLog(l_fragment_shader_id, 512, NULL, l_infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << l_infoLog << std::endl;
		std::cout << p_frgmnt << std::endl;
		glDeleteShader(l_vertex_shader_id);
		glDeleteShader(l_fragment_shader_id);
		return 0;
	}
	// program
	GLuint l_program_id = glCreateProgram();
	glAttachShader(l_program_id, l_vertex_shader_id);
	glAttachShader(l_program_id, l_fragment_shader_id);

	glLinkProgram(l_program_id);
	glValidateProgram(l_program_id);
	glGetProgramiv(l_program_id, GL_LINK_STATUS, &l_success);
	if (l_success == GL_FALSE)
	{
		glGetProgramInfoLog(l_program_id, 512, NULL, l_infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << l_infoLog << std::endl;
		glDeleteShader(l_vertex_shader_id);
		glDeleteShader(l_fragment_shader_id);
		glDeleteProgram(l_program_id);
		return 0;
	}
	glValidateProgram(l_program_id);

	glDeleteShader(l_vertex_shader_id);
	glDeleteShader(l_fragment_shader_id);
	glLinkProgram(0);
	m_id = l_program_id;
	std::cout << "program id " << l_program_id << std::endl;
	return l_program_id;
}
void Shader::set_matrix(const char* name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, &(mat[0][0]));
}
void Shader::set_int(const char* name, GLint val)
{
	glUniform1i(glGetUniformLocation(m_id, name), val);
}
void Shader::set_vec3(const char* name, const glm::vec3& v)
{
	glUniform3fv(glGetUniformLocation(m_id, name), 1, &(v[0]));
}
void Shader::use() const
{
	glUseProgram(m_id);
}
void Shader::unuse() const
{
	glUseProgram(0);
}
void Shader::release()
{
	glUseProgram(0);
	glDeleteProgram(m_id);
}

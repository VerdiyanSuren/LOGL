#include <Shaders/vfShaderLib.h>
#include<sstream>
using namespace vfLOGL;


Shader* ShaderLib::new_shader(const std::string& file)
{
	auto shader = new Shader(file);
	if (shader == nullptr) return nullptr;

	int i = 1;
	std::string name;
	bool finded = false;
	while (!finded) {
		std::stringstream ss;
		ss << DEFAULT_NAME << "_" << i;
		name = ss.str();
		if (get_item_by_name(name.c_str()) == nullptr) break;
		i++;
	}
	shader->set_name(name.c_str());
	m_items.push_back(shader);
	return shader;
}

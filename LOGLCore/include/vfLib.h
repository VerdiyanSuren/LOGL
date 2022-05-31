#ifndef VF_LOGL_LIB_H
#define VF_LOGL_LIB_H

#include <Shaders/vfShaderLib.h>
#include <map>
#include <string>
#include <algorithm>

#define DEFAULT_NAME "default"

namespace vfLOGL
{
	template<class T>
	class Lib
	{
	public:
		//virtual void	read_from_dir() = 0;
		virtual T*		get_item_by_name(const char* name) {
			for (T* item : m_items) {
				if (item->name() == name) return item;
			}
			return nullptr;
		}
		virtual T*		get_default_item() { return m_default;}
		virtual void	delete_item(const char* name) {
			if (name == g_default_name) return;
			T* item = get_item_by_name(name);
			if (item != nullptr){
				m_items.erase(std::remove(m_items.begin(), m_items.end(), item), m_items.end());
				// To Do refresh others
			}
		}
		virtual bool	rename_item(const char* old_name, const char* new_name) {
			if (old_name == g_default_name) return false;
			T* item = get_item_by_name(old_name);
			if (item != nullptr) return false;
			item = get_item_by_name(new_name);
			if (item == nullptr) return false;
			item->set_name(new_name);
			return true;
		}
		virtual void	clear() {
			for (T* item : m_items)
			{
				if (item != nullptr) delete item;
			}
			m_items.clear();
		}
		virtual size_t	size() const { return m_items.size(); }
		T*				get(unsigned int i) { return m_items[i]; }
	protected:
		std::vector<T*> m_items;
		T* m_default = nullptr;
		static const std::string g_default_name;
	};
	template<class T>
	const std::string Lib<T>::g_default_name = DEFAULT_NAME;
}

#endif //!VF_LOGL_LIB_H
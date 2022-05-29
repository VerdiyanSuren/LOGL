#ifndef VF_LOGL_UBO_H
#define VF_LOGL_UBO_H

namespace vfLOGL
{
	class UniformBufferObject
	{
	public:
		UniformBufferObject();
		void realloc(unsigned int bind_point, unsigned int p_size);
		void free();
		void bind() const;
		void unbind() const;
		unsigned int id() const { return m_id; }
	private:
		unsigned int m_buff_size	= 0;
		unsigned int m_id			= 0;
	};
}

#endif //!VF_LOGL_UBO_H
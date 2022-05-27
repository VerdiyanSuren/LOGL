#ifndef VF_LOGL_UBO_H
#define VF_LOGL_UBO_H

namespace vfLOGL
{
	class UniformBufferObject
	{
	public:
		UniformBufferObject(unsigned int p_size);
		void allocate(unsigned int bind_point);
		void free();
		void bind() const;
	private:
		unsigned int m_buff_size;
		unsigned int m_id;
	};
}

#endif //!VF_LOGL_UBO_H
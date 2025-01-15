#pragma once

namespace HyperR {
	class VertexBuffer
	{
	public:
		~VertexBuffer() {};
		void Bind() const;
		void Unbind() const;
		
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
	class IndexBuffer
	{
	public:
		~IndexBuffer() {};
		void Bind() const;
		void Unbind() const;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* vertices, uint32_t size);

	};
}
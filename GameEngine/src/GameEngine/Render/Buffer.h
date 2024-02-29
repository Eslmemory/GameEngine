#pragma once
#include "GameEngine/Core/Core.h"

namespace GE {

	enum class ShaderDataType {
		None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Int:       return 4;
			case ShaderDataType::Int2:		return 2 * 4;
			case ShaderDataType::Int3:		return 3 * 4;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 2 * 4;
			case ShaderDataType::Float3:	return 3 * 4;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 3 * 3 * 4;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}
		GE_ASSERT(false, "Unknow shader data type");
		return 0;
	}

	struct BufferElement {

		std::string m_Name;
		ShaderDataType m_Type;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_Normalized;

		BufferElement();
		BufferElement(ShaderDataType type, std::string name)
			: m_Name(name), m_Type(type), m_Size(ShaderDataTypeSize(type)), m_Offset(0), m_Normalized(false) {}		

		uint32_t GetComponentCount() const {
			switch (m_Type) {
				case ShaderDataType::Int:       return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Bool:		return 1;
			}

			GE_ASSERT(false, "Unknown ShaderDataType! ");
			return 0;
		}
	};

	class GE_API BufferLayout {
	
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) 
		{
			CalculateOffsetAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetBufferElement() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride() {
			int stride = 0;
			for (auto& it : m_Elements) {
				it.m_Offset = stride;
				stride += it.m_Size;
			}
			m_Stride = stride;
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class GE_API VertexBuffer {

	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(void* vertices, uint32_t size);
	};

	class GE_API IndexBuffer {

	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void SetData(void* data, uint32_t count) = 0;
		
		virtual uint32_t GetCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
		static std::shared_ptr<IndexBuffer> Create(uint32_t count);
	};

}
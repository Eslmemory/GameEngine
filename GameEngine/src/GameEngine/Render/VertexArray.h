#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Render/Buffer.h"

namespace GE {

	class GE_API VertexArray {
	public:

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};

}
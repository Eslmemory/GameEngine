#include "gepch.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Render/VertexArray.h"
#include "GameEngine/Render/Buffer.h"
#include "GameEngine/Render/Shader.h"
#include "GameEngine/Camera/Camera.h"
#include "GameEngine/Render/RenderCommand.h"
#include "GameEngine/Manager/ConfigManager.h"
#include "Render2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace GE {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;

		float TexIndex;
	};

	struct LineVertex {
		glm::vec3 Position;
		glm::vec3 Color;

	};

	struct CircleVertex {

	};

	struct Render2DData {
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlot = 32;

		// Quad
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		std::shared_ptr<Shader> QuadShader;


		QuadVertex* QuadVertexBasePtr = nullptr;
		QuadVertex* QuadVertexCurrentPtr = nullptr;
		

		// Line
		std::shared_ptr<VertexArray> LineVertexArray;
		std::shared_ptr<VertexBuffer> LineVertexBuffer;

		LineVertex* LineVertexBasePtr = nullptr;
		LineVertex* LineVertexCurrentPtr = nullptr;

		uint32_t QuadIndexCount, LineVertexCount;
		glm::vec4 QuadVertexPositions[4];

		uint32_t TextureSlotIndex = 1; // 0 is white
		std::array<std::shared_ptr<Texture>, MaxTextureSlot> TextureSlots;

		Render2D::Statistics Stats;
	};

	static Render2DData s_Data;

	void Render2D::Init() {

		// Quad
		s_Data.QuadVertexArray = VertexArray::Create();
		
		BufferLayout quadLayout = {
			{ ShaderDataType::Float3, "a_Postion"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float, "a_TexIndex"}
		};
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout(quadLayout);
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBasePtr = new QuadVertex[s_Data.MaxVertices];

		uint32_t* indices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		std::shared_ptr<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(indices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] indices;

		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadIndexCount = 0;

		s_Data.QuadShader = Shader::Create(ConfigManager::GetInstance().GetAssetFolder() / "Shader/quad.glsl");
		// set white texture
		std::shared_ptr<Texture> whiteTexture = Texture2D::Create(1, 1);
		uint32_t white = 0xffffffff;
		whiteTexture->SetData(&white, 1);
		s_Data.TextureSlots[0] = whiteTexture;

		s_Data.QuadShader->Bind();
		int32_t samplers[s_Data.MaxTextureSlot];
		for (int i = 0; i < s_Data.MaxTextureSlot; i++) {
			samplers[i] = i;
		}
		s_Data.QuadShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlot);

		// Line
		s_Data.LineVertexArray = VertexArray::Create();
		s_Data.LineVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(LineVertex));
		BufferLayout lineLayout = {
			{ ShaderDataType::Float3, "a_Postion"},
			{ ShaderDataType::Float3, "a_Color"}
		};
		s_Data.LineVertexBuffer->SetLayout(lineLayout);
		s_Data.LineVertexArray->AddVertexBuffer(s_Data.LineVertexBuffer);
		LineVertex* LineVertexBasePtr = new LineVertex[s_Data.MaxVertices];

		s_Data.LineVertexCount = 0;
	}

	void Render2D::SceneBegin(const Camera& camera){
		s_Data.QuadShader->Bind();
		s_Data.QuadShader->SetMat4("a_ViewProjection", camera.GetViewProjectionMatrix());
		
		StartBatch();
	}

	void Render2D::SceneEnd() {
		Flush();
		s_Data.Stats.DrawCalls = 0;
		s_Data.Stats.QuadCounts = 0;
	}

	void Render2D::StartBatch() {
		s_Data.QuadVertexCurrentPtr = s_Data.QuadVertexBasePtr;
		s_Data.QuadIndexCount = 0;

		s_Data.LineVertexCurrentPtr = s_Data.LineVertexBasePtr;
		s_Data.LineVertexCount = 0;

		s_Data.TextureSlotIndex = 1;
	}

	void Render2D::NextBatch() {
		Flush();
		StartBatch();
	}

	void Render2D::Flush() {
		// Quad
		if (s_Data.QuadIndexCount) {
			size_t size = (uint8_t*)s_Data.QuadVertexCurrentPtr - (uint8_t*)s_Data.QuadVertexBasePtr;
			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBasePtr, size);

			s_Data.QuadShader->Bind();
			for (int i = 0; i < s_Data.TextureSlotIndex; i++) {
				s_Data.TextureSlots[i]->Bind(i);
			}
			RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
			s_Data.Stats.DrawCalls += 1;
		}
		
	}

	void Render2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))* glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		DrawQuad(transform, color);
	}

	void Render2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		DrawQuad(transform, color);
	}

	void Render2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		DrawQuad(transform, texture, tintColor);
	}

	void Render2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		DrawQuad(transform, texture, tintColor);
	}

	void Render2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 coords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			NextBatch();
		
		for (size_t i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexCurrentPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexCurrentPtr->Color = color;
			s_Data.QuadVertexCurrentPtr->TexCoord = coords[i];
			s_Data.QuadVertexCurrentPtr->TexIndex = 0;
			s_Data.QuadVertexCurrentPtr++;
		}
		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCounts++;
	}

	void Render2D::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor) {
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 coords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		float textureIndex = 0.0f;

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			NextBatch();
		
		for (int i = 1; i < s_Data.TextureSlotIndex; i++) {
			if (*(s_Data.TextureSlots[i].get()) == *(texture.get())) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			if (s_Data.TextureSlotIndex >= s_Data.MaxTextureSlot)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (int i = 0; i < quadVertexCount; i++) {
			s_Data.QuadVertexCurrentPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexCurrentPtr->Color = tintColor;
			s_Data.QuadVertexCurrentPtr->TexCoord = coords[i];
			s_Data.QuadVertexCurrentPtr->TexIndex = textureIndex;
			s_Data.QuadVertexCurrentPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCounts++;
	}

	void Render2D::DrawRotationQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color){
		DrawRotationQuad(glm::vec3(position, 0.0f), size, rotation, color);
	}

	void Render2D::DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color){
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		DrawQuad(transform, color);
	}

	void Render2D::DrawRotationQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor) {
		DrawRotationQuad(glm::vec3(position, 0.0f), size, rotation, texture, tintColor);
	}

	void Render2D::DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
		DrawQuad(transform, texture, tintColor);
	}

	void Render2D::DrawSprite(const glm::mat4& transform, SpriteComponent& sprite) {
		if (sprite.Texture) {
			DrawQuad(transform, sprite.Texture, sprite.Color);
		}
		else {
			DrawQuad(transform, sprite.Color);
		}
	}

}
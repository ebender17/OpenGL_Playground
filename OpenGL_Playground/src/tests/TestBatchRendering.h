#pragma once

#include "Test.h"

#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <memory>

namespace test {

	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering();
		~TestBatchRendering();

		void OnUpdate(float deltaTime) override;
		void OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_TextureOne;
		std::unique_ptr<Texture> m_TextureTwo;
	};

}


#pragma once

#include "Test.h"

#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <memory>

namespace test
{

	class TestTexture2DNonAPI : public Test
	{
	public:
		TestTexture2DNonAPI();
		~TestTexture2DNonAPI();

		void OnUpdate(float deltaTime) override;
		void OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight) override;
		void OnImGuiRender() override;
	private:
		/*std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Texture> m_Texture;*/
		unsigned int m_VAO, m_VBO, m_EBO, m_Texture;
		std::unique_ptr<Shader> m_Shader;

		glm::vec3 m_TranslationA, m_TranslationB, m_ColorA, m_ColorB;
	};

}


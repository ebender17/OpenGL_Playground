#pragma once

#include "Test.h"

#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <memory>

namespace test {

	class TestBasicLighting : public Test
	{
	public:
		TestBasicLighting();
		~TestBasicLighting();

		void OnUpdate(float deltaTime) override;
		void OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_LightingShader;
		std::unique_ptr<Shader> m_LightCubeShader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_LightColorA, m_ObjectColor, m_LightPosition;
	};

}


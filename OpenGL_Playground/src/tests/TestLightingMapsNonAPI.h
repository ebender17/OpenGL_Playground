#pragma once

#include "Test.h"

#include "Shader.h"
#include "ObjectProperties.h"

namespace test {

	class TestLightingMapsNonAPI : public Test
	{
	public:
		TestLightingMapsNonAPI();
		~TestLightingMapsNonAPI();

		void OnUpdate(float deltaTime) override;
		void OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_LightingShader;
		std::unique_ptr<Shader> m_LightCubeShader;
		unsigned int m_VAO, m_VBO;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_LightPosition;
		MaterialTextures m_ObjectMaterial;
		Light m_Light;
	};

}


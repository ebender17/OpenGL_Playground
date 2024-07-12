#pragma once

#include "Test.h"

#include "Shader.h"
#include "ObjectProperties.h"

#include <memory>

namespace test {

	class TestBasicLightingNonAPI : public Test
	{
	public:
		TestBasicLightingNonAPI();
		~TestBasicLightingNonAPI();

		void OnUpdate(float deltaTime) override;
		void OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_LightingShader;
		std::unique_ptr<Shader> m_LightCubeShader;
		unsigned int m_VAO, m_VBO;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_LightPosition;
		Material m_ObjectMaterial;
		Light m_Light;
	};

}


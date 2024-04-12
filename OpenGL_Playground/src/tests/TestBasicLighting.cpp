#include "TestBasicLighting.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace test {

	TestBasicLighting::TestBasicLighting()
        : m_LightColorA(1.0f, 1.0f, 1.0f), m_ObjectColor(1.0f, 0.5f, 0.31f), m_LightPosition(0.0f, 1.2f, 1.2f)
	{
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        GLCall(glEnable(GL_DEPTH_TEST));

        m_LightingShader = std::make_unique<Shader>("res/shaders/BasicLighting.shader");
        m_LightCubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
	}

	TestBasicLighting::~TestBasicLighting()
	{
	}

	void TestBasicLighting::OnUpdate(float deltaTime)
	{
	}

	void TestBasicLighting::OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight)
	{
        Renderer renderer;

        m_LightPosition.y = 1.5f * sin(glfwTime);
        m_LightPosition.z = 1.5f * cos(glfwTime);

        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalWorld = glm::mat3(1.0f);
        normalWorld = glm::transpose(glm::inverse(model));

        // TODO : Pre-multiply matrices needed in shader instead of doing in shader
        m_LightingShader->Bind();
        m_LightingShader->SetUniformMat4f("u_Projection", projection);
        m_LightingShader->SetUniformMat4f("u_View", view);
        m_LightingShader->SetUniformMat4f("u_Model", model);
        m_LightingShader->SetUniformMat3f("u_NormalWorld", normalWorld);
        m_LightingShader->SetUniformVec3f("u_ObjectColor", m_ObjectColor);
        m_LightingShader->SetUniformVec3f("u_LightColor", m_LightColorA);
        m_LightingShader->SetUniformVec3f("u_LightPos", m_LightPosition);
        m_LightingShader->SetUniformVec3f("u_ViewPos", camera.GetPosition());

        renderer.Draw(*m_VAO, 0, 36, *m_LightingShader);

        m_LightCubeShader->Bind();
        m_LightCubeShader->SetUniformMat4f("u_Projection", projection);
        m_LightCubeShader->SetUniformMat4f("u_View", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, m_LightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        m_LightCubeShader->SetUniformMat4f("u_Model", model);
        m_LightCubeShader->SetUniformVec3f("u_Color", m_LightColorA);

        renderer.Draw(*m_VAO, 0, 36, *m_LightCubeShader);
	}

	void TestBasicLighting::OnImGuiRender()
	{
        ImGui::ColorEdit3("Object color", (float*)&m_ObjectColor[0]);
        ImGui::ColorEdit3("Light color", (float*)&m_LightColorA[0]);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
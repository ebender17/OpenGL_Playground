#include "TestBasicLightingNonAPI.h"

#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace test {

    TestBasicLightingNonAPI::TestBasicLightingNonAPI()
        : m_LightPosition(0.0f, 1.2f, 1.2f)
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
        // m_EnableInput = true;

        m_LightingShader = std::make_unique<Shader>("res/shaders/PhongLighting.shader");
        m_LightCubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

        GLCall(glGenVertexArrays(1, &m_VAO));
        GLCall(glGenBuffers(1, &m_VBO));

        GLCall(glBindVertexArray(m_VAO));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
        GLCall(glEnableVertexAttribArray(0));

        GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
        GLCall(glEnableVertexAttribArray(1));

        m_Light = Light(
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        m_ObjectMaterial = MaterialFlatColor(
            glm::vec3(0.0f, 0.1f, 0.06f),
            glm::vec3(0.0f, 0.50980392f, 0.50980392f),
            glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
            32.0f
        );
    }

    TestBasicLightingNonAPI::~TestBasicLightingNonAPI()
    {
        GLCall(glDeleteVertexArrays(1, &m_VAO));
        GLCall(glDeleteBuffers(1, &m_VBO));
    }

    void TestBasicLightingNonAPI::OnUpdate(float deltaTime)
    {
    }

    void TestBasicLightingNonAPI::OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight)
    {
        m_LightPosition.y = 1.5f * sin(glfwTime);
        m_LightPosition.z = 1.5f * cos(glfwTime);

        m_LightingShader->Bind();
        m_LightingShader->SetUniformVec3f("u_Light.position", m_LightPosition);

        // light properties
        m_LightingShader->SetUniformVec3f("u_Light.ambient", m_Light.Ambient);
        m_LightingShader->SetUniformVec3f("u_Light.diffuse", m_Light.Diffuse);
        m_LightingShader->SetUniformVec3f("u_Light.specular", m_Light.Specular);

        // material properties
        m_LightingShader->SetUniformVec3f("u_Material.ambient", m_ObjectMaterial.Ambient);
        m_LightingShader->SetUniformVec3f("u_Material.diffuse", m_ObjectMaterial.Diffuse);
        m_LightingShader->SetUniformVec3f("u_Material.specular", m_ObjectMaterial.Specular);
        m_LightingShader->SetUniform1f("u_Material.shininess", m_ObjectMaterial.Shininess);

        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalWorld = glm::mat3(1.0f);
        normalWorld = glm::transpose(glm::inverse(model));

        m_LightingShader->SetUniformMat4f("u_ProjectionView", projection * view);
        m_LightingShader->SetUniformMat4f("u_Model", model);
        m_LightingShader->SetUniformMat3f("u_NormalWorld", normalWorld);
        m_LightingShader->SetUniformVec3f("u_ViewPos", camera.GetPosition());

        GLCall(glBindVertexArray(m_VAO));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        m_LightCubeShader->Bind();
        model = glm::mat4(1.0f);
        model = glm::translate(model, m_LightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        m_LightCubeShader->SetUniformMat4f("u_MVP", projection * view * model);
        m_LightCubeShader->SetUniformVec3f("u_Color", m_Light.Diffuse);

        GLCall(glBindVertexArray(m_VAO));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    }

    void TestBasicLightingNonAPI::OnImGuiRender()
    {
        ImGui::ColorEdit3("Object ambient", (float*)&m_ObjectMaterial.Ambient[0]);
        ImGui::ColorEdit3("Object diffuse", (float*)&m_ObjectMaterial.Diffuse[0]);
        ImGui::ColorEdit3("Object specular", (float*)&m_ObjectMaterial.Specular[0]);
        ImGui::InputFloat("Object shininess", &m_ObjectMaterial.Shininess);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

}

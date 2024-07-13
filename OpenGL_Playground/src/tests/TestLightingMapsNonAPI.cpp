#include "TestLightingMapsNonAPI.h"

#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "stb_image/stb_image.h"

namespace test {

	TestLightingMapsNonAPI::TestLightingMapsNonAPI()
	{
        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
        
        GLCall(glEnable(GL_DEPTH_TEST));
        m_EnableInput = true;

        // TODO - add emissive
        GLCall(glGenVertexArrays(1, &m_VAO));
        GLCall(glGenBuffers(1, &m_VBO));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        GLCall(glBindVertexArray(m_VAO));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
        GLCall(glEnableVertexAttribArray(1));
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
        GLCall(glEnableVertexAttribArray(2));
        // TODO - add emissive

        m_LightingShader = std::make_unique<Shader>("res/shaders/LightingMaps.shader");
        m_LightCubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

        m_Light = Light(
            glm::vec3(0.2f, 0.2f, 0.2f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        m_ObjectMaterial = MaterialTextures(0, 1, 2, 32.0f);

        GLCall(glGenTextures(1, &m_ObjectMaterial.Diffuse));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_ObjectMaterial.Diffuse));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        int width, height, nrChannels;
        const char* pathDiffuse = "res/textures/wooden-box-diffuse.png";
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* dataDiffuse = stbi_load(pathDiffuse, &width, &height, &nrChannels, 0);
        if (dataDiffuse)
        {
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataDiffuse));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        }
        else
        {
            std::cout << "Failed to load texture " << std::endl;
            std::cout << stbi_failure_reason() << std::endl;
        }
        stbi_image_free(dataDiffuse);

        GLCall(glGenTextures(1, &m_ObjectMaterial.Specular));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_ObjectMaterial.Specular));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        const char* pathSpecular = "res/textures/wooden-box-specular.png";
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* dataSpecular = stbi_load(pathSpecular, &width, &height, &nrChannels, 0);
        if (dataSpecular)
        {
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataSpecular));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        }
        else
        {
            std::cout << "Failed to load texture " << std::endl;
            std::cout << stbi_failure_reason() << std::endl;
        }
        stbi_image_free(dataSpecular);

        // TODO - load emissive

        m_LightingShader->Bind();
        m_LightingShader->SetUniform1i("u_Material.diffuse", m_ObjectMaterial.Diffuse);
        m_LightingShader->SetUniform1i("u_Material.specular", m_ObjectMaterial.Specular);
        // TODO - add emissive
	}

	TestLightingMapsNonAPI::~TestLightingMapsNonAPI()
	{
        GLCall(glDeleteVertexArrays(1, &m_VAO));
        GLCall(glDeleteBuffers(1, &m_VBO));
	}

	void TestLightingMapsNonAPI::OnUpdate(float deltaTime)
	{
	}

	void TestLightingMapsNonAPI::OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight)
	{
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        m_LightingShader->Bind();
        m_LightingShader->SetUniformVec3f("u_Light.position", lightPos);
        m_LightingShader->SetUniformVec3f("u_ViewPos", camera.GetPosition());

        m_LightingShader->SetUniformVec3f("u_Light.ambient", m_Light.Ambient);
        m_LightingShader->SetUniformVec3f("u_Light.diffuse", m_Light.Diffuse);
        m_LightingShader->SetUniformVec3f("u_Light.specular", m_Light.Specular);

        m_LightingShader->SetUniform1f("u_Material.shininess", 64.0f);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalWorld = glm::mat3(1.0f);
        normalWorld = glm::transpose(glm::inverse(model));

        m_LightingShader->SetUniformMat4f("u_ProjectionView", projection * view);
        m_LightingShader->SetUniformMat4f("u_Model", model);
        m_LightingShader->SetUniformMat3f("u_NormalWorld", normalWorld);

        GLCall(glActiveTexture(GL_TEXTURE0));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_ObjectMaterial.Diffuse));
        GLCall(glActiveTexture(GL_TEXTURE1));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_ObjectMaterial.Specular));

        glBindVertexArray(m_VAO);
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

	void TestLightingMapsNonAPI::OnImGuiRender()
	{
	}

}

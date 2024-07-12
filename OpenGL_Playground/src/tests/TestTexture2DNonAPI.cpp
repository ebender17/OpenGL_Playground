#include "TestTexture2DNonAPI.h"

#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "stb_image/stb_image.h"

namespace test
{

	TestTexture2DNonAPI::TestTexture2DNonAPI()
		: m_TranslationA(1, 1, -0.5), m_TranslationB(-1, 1, -0.5), m_ColorA(1.0f, 1.0f, 1.0f), m_ColorB(1.0f, 1.0f, 1.0f)
	{
		float vertices[] = {
			// positions         // texture coords
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCall(glGenVertexArrays(1, &m_VAO));
		GLCall(glGenBuffers(1, &m_VBO));
		GLCall(glGenBuffers(1, &m_EBO));

		GLCall(glBindVertexArray(m_VAO));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

		// position attribute
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
		GLCall(glEnableVertexAttribArray(0));
		// texture coord attribute
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
		GLCall(glEnableVertexAttribArray(1));

		// generate texture
		GLCall(glGenTextures(1, &m_Texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));

		// set the texture wrapping parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		// set texture filtering parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		const char* path = "res/textures/wooden-box.png";
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else
		{
			std::cout << "Failed to load texture " << std::endl;
			std::cout << stbi_failure_reason() << std::endl;
		}
		stbi_image_free(data);

		m_Shader = std::make_unique<Shader>("res/shaders/Texture2D.shader");
		m_Shader->Bind();
	}

	TestTexture2DNonAPI::~TestTexture2DNonAPI()
	{
		GLCall(glDeleteVertexArrays(1, &m_VAO));
		GLCall(glDeleteBuffers(1, &m_VBO));
		GLCall(glDeleteBuffers(1, &m_EBO));
	}

	void TestTexture2DNonAPI::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2DNonAPI::OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glActiveTexture(GL_TEXTURE0)); // default active texture unit is 0 so don't need to technically activate here
		GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
		m_Shader->SetUniform1i("u_Texture", 0);

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = projection * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->SetUniform4f("u_Color", m_ColorA.r, m_ColorA.g, m_ColorA.b, 1.0f);
			GLCall(glBindVertexArray(m_VAO)); // only need to bind VAO as it stores VB & EBO
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = projection * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Shader->SetUniform4f("u_Color", m_ColorB.r, m_ColorB.g, m_ColorB.b, 1.0f);
			GLCall(glBindVertexArray(m_VAO));
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		}
	}

	void TestTexture2DNonAPI::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, -2.0f, 2.0f);
		ImGui::ColorEdit3("Color A", (float*)&m_ColorA[0]);
		ImGui::ColorEdit3("Color B", (float*)&m_ColorB[0]);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}

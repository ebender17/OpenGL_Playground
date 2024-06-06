#include "TestBatchRendering.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestBatchRendering::TestBatchRendering()
	{
		float vertices[] = {
			 -1.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 -0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
			 -0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f,
			 -1.5f,  0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 1.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 1.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/BatchRendering.shader");
		m_Shader->Bind();
		m_TextureOne = std::make_unique<Texture>("res/textures/wooden-box.png", true, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		m_TextureTwo = std::make_unique<Texture>("res/textures/character-sprite.png", true, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);
	}

	TestBatchRendering::~TestBatchRendering()
	{

	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{

	}

	void TestBatchRendering::OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight)
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_TextureOne->Bind(0);
		m_TextureTwo->Bind(1);

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 mvp = projection * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestBatchRendering::OnImGuiRender()
	{

	}

}

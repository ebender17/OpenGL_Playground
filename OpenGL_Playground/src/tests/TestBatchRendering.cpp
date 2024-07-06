#include "TestBatchRendering.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace test {

	TestBatchRendering::TestBatchRendering()
	{
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 1000, GL_DYNAMIC_DRAW);
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

	std::array<Vertex, 4> TestBatchRendering::CreateQuad(float x, float y, float textureID)
	{
		float size = 1.0f;

		Vertex v0;
		v0.Position = { x, y, 0.0f };
		v0.Color = { 0.0f, 0.5f, 0.5f, 1.0f };
		v0.TexCoords = { 0.0f, 0.0f };
		v0.TexID = textureID;

		Vertex v1;
		v1.Position = { (x + size), y, 0.0f };
		v1.Color = { 1.0f, 0.5f, 0.0f, 1.0f };
		v1.TexCoords = { 1.0f, 0.0f };
		v1.TexID = textureID;

		Vertex v2;
		v2.Position = { (x + size), (y + size), 0.0f };
		v2.Color = { 0.5f, 1.0f, 0.5f, 1.0f };
		v2.TexCoords = { 1.0f, 1.0f };
		v2.TexID = textureID;

		Vertex v3;
		v3.Position = { x, (y + size), 0.0f };
		v3.Color = { 0.0f, 0.5f, 1.0f, 1.0 };
		v3.TexCoords = { 0.0f, 1.0f };
		v3.TexID = textureID;
		return std::array<Vertex, 4>({ { v0, v1, v2, v3 } });
	}

	void TestBatchRendering::OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight)
	{
		auto quad0 = CreateQuad(m_Quad0Position[0], m_Quad0Position[1], 0.0f);
		auto quad1 = CreateQuad(0.5f, -0.5f, 1.0f);

		Vertex vertices[8];
		memcpy(vertices, quad0.data(), quad0.size() * sizeof(Vertex));
		memcpy(vertices + quad0.size(), quad1.data(), quad1.size() * sizeof(Vertex));

		m_VertexBuffer->Bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));

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
		ImGui::DragFloat2("Quad0 Position", m_Quad0Position, 0.1f);
	}

}

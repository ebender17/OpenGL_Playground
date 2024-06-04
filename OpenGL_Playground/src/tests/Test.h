#pragma once

#include <vector>
#include <iostream>
#include <functional>

#include "glm/glm.hpp"
#include "Camera.h"

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(double glfwTime, const Camera& camera, float screenWidth, float screenHeight) {}
		virtual void OnImGuiRender() {}

		inline bool GetEnableInput() const { return m_EnableInput; }
	protected:
		bool m_EnableInput = false;
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};

}

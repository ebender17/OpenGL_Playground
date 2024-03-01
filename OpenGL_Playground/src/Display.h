#pragma once

#include <GLFW/glfw3.h>

class Display
{
public:
	Display(unsigned int width, unsigned int height, const char* name);
	~Display();

	bool Setup();

	inline GLFWwindow* GetWindow() const { return m_Window; }
private:
	unsigned int m_Width;
	unsigned int m_Height;

	const char* m_Name;

	GLFWwindow* m_Window;
};


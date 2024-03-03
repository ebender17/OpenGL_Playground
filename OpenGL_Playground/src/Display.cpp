#include "Display.h"

Display::Display(unsigned int width, unsigned int height, const char* name)
	: m_Width(width), m_Height(height), m_Name(name), m_Window(nullptr)
{
}

Display::~Display()
{
    if(m_Window)
        glfwTerminate();
}

bool Display::Setup()
{
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    return true;
}

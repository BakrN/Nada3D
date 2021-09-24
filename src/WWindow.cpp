#include "WWindow.h"
#include <iostream>
void error_callback(int code, const char* description)
{
	std::cout << "Error Code (" << code << "): " << description << std::endl;
}
void WWindow::Init()
{
	if (!glfwInit()) {
		std::cout << "Error with initialization: " << std::endl; 
	}
	glfwSetErrorCallback(error_callback);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
	glfwSetKeyCallback(m_Window, OnKey);
	glfwSetMouseButtonCallback(m_Window, OnMouse);
	glfwSetScrollCallback(m_Window, OnScroll);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window,this);

}

void WWindow::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}


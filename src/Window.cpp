#include "Window.h"
#include <iostream>

void TestWindow::OnKey(int key, int scancode, int actions, int mods)
{
	
}

void TestWindow::OnMouse(int button, int action, int mods)
{
}

void TestWindow::OnScroll(double xoffset, double yoffset)
{
	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);
	xpos = xpos - m_Width/2; 
	ypos = -(ypos - m_Height/2); 
	float m_Scale = (yoffset > 0) ? 1.08f : 0.92;
	this->m_WindowCamera->Zoom(m_Scale, xpos, ypos);
	std::cout << "Y OFFSET: " << yoffset << std::endl;
}

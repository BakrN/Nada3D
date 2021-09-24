#pragma once
#include <GLFW/glfw3.h> 
#include <string>
class WWindow {
public: 
	float GetWidth() const { return m_Width; };
	float GetHeight() const { return m_Height; };
	GLFWwindow* GetWindow() { return m_Window; };
	virtual void Init();
	virtual void Update();
private:
		float m_Width;
		float m_Height;
		std::string m_Name;

		WWindow(float width,float height, const std::string& windowname)
		{	
			m_Width = width; 
			m_Height = height; 
			m_Name = windowname; 
		}

		virtual  ~WWindow()
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		virtual void OnKey(int key, int scancode, int actions, int mods) = 0; 
		virtual void OnMouse(int button, int action, int mods) = 0;
		virtual void OnScroll(double xoffset, double yoffset) = 0;
		
		
	GLFWwindow* m_Window;
	friend class TestWindow;
	static void OnKey(GLFWwindow* window, int key, int scancode, int actions, int mods)
	{
		WWindow* obj = (WWindow*)glfwGetWindowUserPointer(window);
		obj->OnKey(key, scancode, actions, mods);
	}
	static void OnMouse(GLFWwindow* window, int button, int action, int mods)
	{
		WWindow* obj = (WWindow*)glfwGetWindowUserPointer(window);
		obj->OnMouse(button,action,mods);
	}
	static void OnScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		WWindow* obj = (WWindow*)glfwGetWindowUserPointer(window);
		obj->OnScroll(xoffset,yoffset);
	}
	
};

#pragma once
#include "WWindow.h"
#include "Camera.h"
#include <memory>
class TestWindow :	public WWindow {
private: 
	std::shared_ptr<Camera> m_WindowCamera; 
	float m_Scale = 1.0f; 
public:

	TestWindow(float width, float height, const char* windowname) : WWindow(width, height, windowname) {};
	// Inherited via WWindow
	void AttatchCamera(const std::shared_ptr<Camera>& Cam) { m_WindowCamera = Cam;  };
	virtual void OnKey(int key, int scancode, int actions, int mods) override;

	virtual void OnMouse(int button, int action, int mods) override;

	virtual void OnScroll(double xoffset, double yoffset) override;

};

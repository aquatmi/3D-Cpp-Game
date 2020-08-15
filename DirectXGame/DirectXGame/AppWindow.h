#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow: public Window
{
public:
	AppWindow() = default;

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
};


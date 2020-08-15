#pragma once
#include <Windows.h>



class Window
{
public:
	// initialise window
	Window();
	bool init();
	void broadcast();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	// EVENTS
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();

	// release window
	~Window();

protected:
	HWND m_hwnd = nullptr;
	// flag to indicate window running
	bool m_is_run = true;
};


#include "Window.h"
#include <stdexcept>

Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

Window::Window()
{
}

bool Window::init()
{
	// create window class
	WNDCLASSEX wc{}; // Using {} to initialize a struct sets all fields to 0 in C++
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"MyWindowClass";
	wc.lpfnWndProc = &WndProc;

	// if window class creation fails, stop application
	if (!RegisterClassEx(&wc))
		throw std::runtime_error("Failed to Create Window Class.");

	//Creating window size
	RECT rect = { 0,0,1280,720 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
	
	const auto width = rect.right - rect.left;
	const auto height = rect.bottom - rect.top;

	if (!window)
		window = this;

	// create window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass",
		L"DirectXApplication", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, width, height, nullptr, nullptr, nullptr, this);

	// if window creation fails, stop application
	if (!m_hwnd)
		throw std::runtime_error("Failed to initialize Window.");

	// show the window
	ShowWindow(m_hwnd, SW_SHOW);
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CREATE: {
		//event for when window created
		//collect here
		auto* const params = reinterpret_cast<LPCREATESTRUCT>(lparam);
		auto* const window = reinterpret_cast<Window* const>(params->lpCreateParams);

		//store for later
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->setHWND(hwnd);
		window->OnCreate();
		break;

	}

	case WM_DESTROY: {
		//event for when window destroyed
		auto* const window = reinterpret_cast<Window* const>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		window->OnDestroy();
		PostQuitMessage(0);
		break;
	}

	default: 
		return DefWindowProc(hwnd, msg, wparam, lparam);
	} //end switch

	return 0;
}

void Window::broadcast()
{
	MSG msg{};

	OnUpdate();
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	Sleep(1);
}


bool Window::isRun()
{
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT client_rect;
	::GetClientRect(this->m_hwnd, &client_rect);
	return client_rect;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	// set the flag to show the window isnt running
	m_is_run = false;
}

Window::~Window()
{
	DestroyWindow(m_hwnd);
}

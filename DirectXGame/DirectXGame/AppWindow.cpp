#include "AppWindow.h"

void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::get()->init();

	RECT client_rect = this->getClientWindowRect();
	UINT cr_width = client_rect.right - client_rect.left;
	UINT cr_height = client_rect.bottom - client_rect.top;

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	m_swap_chain->init(this->m_hwnd, cr_width, cr_height);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::get()->getImmidiateDeviceContext()->ClearRenderTargetColour(this->m_swap_chain, 1, 0, 0, 1);
	

	m_swap_chain->present(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

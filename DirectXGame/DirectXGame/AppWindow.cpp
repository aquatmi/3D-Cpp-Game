#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};


void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::get()->init();

	RECT client_rect = this->getClientWindowRect();
	UINT cr_width = client_rect.right - client_rect.left;
	UINT cr_height = client_rect.bottom - client_rect.top;

	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	m_swap_chain->init(this->m_hwnd, cr_width, cr_height);

	vertex list[] = {
		//X		 Y	   Z
		{-0.5f, -0.5f, 0.0f},
		{ 0.0f,  0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f}
	};

	m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();
	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vertex_buffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::get()->getImmidiateDeviceContext()->ClearRenderTargetColour(this->m_swap_chain, 1, 0, 1, 1);
	
	RECT client_rect = this->getClientWindowRect();
	UINT cr_width = client_rect.right - client_rect.left;
	UINT cr_height = client_rect.bottom - client_rect.top;
	
	GraphicsEngine::get()->getImmidiateDeviceContext()->setViewportSize(cr_width, cr_height);
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmidiateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	GraphicsEngine::get()->getImmidiateDeviceContext()->drawTriangleList(m_vertex_buffer->getSizeVertex(), 0);

	m_swap_chain->present(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vertex_buffer->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

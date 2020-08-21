#pragma once
#include <d3d11.h>
#include "VertexBuffer.h"

class SwapChain;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	void ClearRenderTargetColour(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);

	bool Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;

	friend class SwapChain;
};


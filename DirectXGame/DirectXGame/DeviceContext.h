#pragma once
#include <d3d11.h>

class SwapChain;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool ClearRenderTargetColour(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	bool Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;

	friend class SwapChain;
};

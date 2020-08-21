#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context)
{
}

bool DeviceContext::ClearRenderTargetColour(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_colour[] = { red, green, blue, alpha };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_colour);
	return false;
}

bool DeviceContext::Release()
{
	m_device_context->Release();
	delete this;
	return true;
}

DeviceContext::~DeviceContext()
{
}

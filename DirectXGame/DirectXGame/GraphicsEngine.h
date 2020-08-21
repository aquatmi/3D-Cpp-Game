#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

class GraphicsEngine
{
public:
	GraphicsEngine();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~GraphicsEngine();

	static GraphicsEngine* get();

	SwapChain* createSwapChain();
	DeviceContext* getImmidiateDeviceContext();
	VertexBuffer* createVertexBuffer();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	DeviceContext* m_imm_device_context;

	IDXGIDevice* m_dxgi_device;	
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	friend class SwapChain;
	friend class VertexBuffer;
};
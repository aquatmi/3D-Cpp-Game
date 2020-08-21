#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init() // Load DirectX Resources
{
	// the different types of driver, in descending levels of good-ness
	D3D_DRIVER_TYPE driver_types[] =
	{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
	};
	// length of the array for itterating through
	UINT num_driver_types = ARRAYSIZE(driver_types);

	// different feature levels, needs to be as an array even with only one level
	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	// length of array needed for creating device
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	ID3D11DeviceContext* m_imm_context;

	HRESULT result = 0;	// checker to see if driver loaded correctly
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++) {
		// for each driver type, attempt to create a device
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		// if device successfully created, break loop, we got it
		if (SUCCEEDED(result)) {
			break;
		}
	}
	// if after the for loop, a device has not been successfully started, close.
	if (FAILED(result)) {
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);


	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	return true;
}

bool GraphicsEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	// Release DirectX Resources
	m_imm_device_context->Release();
	m_d3d_device->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmidiateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

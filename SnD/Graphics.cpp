#include "Graphics.h"
using namespace snd_graphics;

Graphics::Graphics(HWND hWnd, int window_width, int window_height, int RR)
{
	this->hWnd          = hWnd;
	this->window_width  = window_width;
	this->window_height = window_height;
	this->RR            = RR;
}

Graphics::~Graphics()
{
	d3d_device->Release();
	d3d_context->Release();
	dxgi_swapchain->Release();
	d3d_rtv->Release();
}

void Graphics::init()
{
	DXGI_SWAP_CHAIN_DESC swap_description = {};
	swap_description.BufferCount = 2;
	swap_description.BufferDesc.Height = window_height;
	swap_description.BufferDesc.Width = window_width;
	swap_description.BufferDesc.RefreshRate.Numerator   = RR;
	swap_description.BufferDesc.RefreshRate.Denominator = 1;
	swap_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_description.OutputWindow = hWnd;
	swap_description.SampleDesc.Count = 1;
	swap_description.SampleDesc.Quality = 4;
	swap_description.Windowed = true;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP,
		nullptr, 0,
		nullptr, 0,
		D3D11_SDK_VERSION, &swap_description,
		&dxgi_swapchain, &d3d_device,
		nullptr, &d3d_context))) {
		throw;
	}

	ID3D11Texture2D *backbuffer_handle = 0;
	if (FAILED(dxgi_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backbuffer_handle))) {
		throw;
	}
	if (FAILED(d3d_device->CreateRenderTargetView(backbuffer_handle, nullptr, &d3d_rtv))) {
		throw;
	}

	d3d_context->OMSetRenderTargets(1, &d3d_rtv, nullptr);

	D3D11_VIEWPORT view = {};
	view.Height = window_height;
	view.Width = window_width;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;

	d3d_context->RSSetViewports(1, &view);
}

void Graphics::clearBackBuffer()
{
	float clearcolor[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	d3d_context->ClearRenderTargetView(d3d_rtv, clearcolor);
}

void Graphics::swapBuffers()
{
	dxgi_swapchain->Present(0, 1);
}


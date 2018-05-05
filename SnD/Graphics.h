#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>

namespace snd_graphics
{
	class Graphics
	{
	public:
		Graphics(HWND hWnd,
			     int  window_width, 
			     int  window_height, 
			     int  RR);
		~Graphics();
	public:
		void init();
		void clearBackBuffer();
		void swapBuffers();
	private:
		ID3D11Device           *d3d_device;
		ID3D11DeviceContext    *d3d_context;
		IDXGISwapChain         *dxgi_swapchain;
		ID3D11RenderTargetView *d3d_rtv;

		int  window_width, window_height, RR;
		HWND    hWnd;
		HRESULT hr;
	};
};


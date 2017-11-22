#ifndef D3DCLASS_H
#define D3DCLASS_H

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cuda_d3d10_interop.h>

#include <d3d10.h>
#include <d3dx10.h>

class d3dClass
{
public:
	D3D10_DRIVER_TYPE					g_driverType;
	ID3D10Device*					    g_pd3dDevice;
	IDXGISwapChain*					    g_pSwapChain;
	ID3D10Texture2D*                    pBackBuffer;
	ID3D10RenderTargetView*             g_pRenderTargetView;

	ID3D10Texture2D						*cuda_pTexture;
	ID3D10ShaderResourceView			*cuda_pResource;
	cudaGraphicsResource				*cudaResource;

	int									cuda_width;
	int									cuda_height;
	int	 size_3 = 0;
	int	 size_4 = 0;
	UINT width;
	UINT height;

	int temp=0;

	HRESULT InitDevice(HWND& g_hWnd, int& bk_width, int& bk_height);//Init
	void buildTexture(int framewidth, int frameheight);//Init

	void Render(unsigned char* cudaLinearMemory);
	void CleanupDevice();
};
#endif

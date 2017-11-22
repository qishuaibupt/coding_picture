#include "d3d_class.h"

HRESULT d3dClass::InitDevice(HWND&  g_hWnd, int& bk_width, int& bk_height)
{
	HRESULT hr = S_OK;

	width = bk_width;
	height = bk_height;

	cuda_width = width;
	cuda_height = height;

	UINT createDeviceFlags = 0;

	D3D10_DRIVER_TYPE driverTypes[] =
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	DXGI_SWAP_CHAIN_DESC sd;//1.creat swap_chain_desc
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;//句柄
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags,
			D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice);//2.creat_swap_chain_interface
		if (SUCCEEDED(hr))//如果hardware不成功 就选择reference
			break;
	}
	if (FAILED(hr))
		return hr;

	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);//3.创建backbuffer
	if (FAILED(hr))//4.绑定backbuffer
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();//5.创建绘制目标视图
	if (FAILED(hr))
		return hr;
	g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);//6.合并输出
	//不需要深度信息 所以为NULL
	size_3 = width*height * 3 * sizeof(unsigned char);
	size_4 = width*height * 4 * sizeof(unsigned char);

	return S_OK;
}


void d3dClass::buildTexture(int framewidth, int frameheight)
{

	cuda_width = framewidth;
	cuda_height = frameheight;

	D3D10_TEXTURE2D_DESC desc;//1.创建 texture desc
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = framewidth;  //2.设置texture_desc属性
	desc.Height = frameheight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;

	g_pd3dDevice->CreateTexture2D(&desc, NULL, &cuda_pTexture);//3.创建texture 对指针赋值//cuda_pTextrure指向纹理

	//注册cuda纹理
	cudaGraphicsD3D10RegisterResource(&cudaResource, cuda_pTexture, cudaGraphicsRegisterFlagsNone);
}


void d3dClass::Render(unsigned char* cudaLinearMemory)
{
	
	cudaGraphicsMapResources(1, &cudaResource, 0);//map复制数据到纹理 cuda已经运行完毕 取走数据

	//中断 显存没有数据
	cudaArray *cuArray;
	cudaGraphicsSubResourceGetMappedArray((cudaArray_t*)(&cuArray), cudaResource, 0, 0);
	cudaMemcpyToArray(cuArray, 0, 0, cudaLinearMemory, width*height* 4 * sizeof(unsigned char), cudaMemcpyDeviceToDevice);
	
	cudaGraphicsUnmapResources(1, &cudaResource, 0); ///unmap恢复d3dbuffer使用权//!!


	//Clear the back buffer
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // red, green, blue, alpha
	g_pd3dDevice->ClearRenderTargetView(g_pRenderTargetView, ClearColor);//填充黑色
	

	//// Present our back buffer to our front buffer
	g_pd3dDevice->CopyResource(pBackBuffer, cuda_pTexture);//填充back buffer cuda_pTexture中为数据
	//填充back buffer
	pBackBuffer->Release();

	g_pSwapChain->Present(0, 0);
}


void d3dClass::CleanupDevice()
{
	cudaGraphicsUnregisterResource(cudaResource);
	
	//if (g_pRenderTargetView) 
		//g_pRenderTargetView->Release();
	//if (g_pd3dDevice) 
		//g_pd3dDevice->Release();
}
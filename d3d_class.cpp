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
	sd.OutputWindow = g_hWnd;//���
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags,
			D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice);//2.creat_swap_chain_interface
		if (SUCCEEDED(hr))//���hardware���ɹ� ��ѡ��reference
			break;
	}
	if (FAILED(hr))
		return hr;

	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);//3.����backbuffer
	if (FAILED(hr))//4.��backbuffer
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();//5.��������Ŀ����ͼ
	if (FAILED(hr))
		return hr;
	g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);//6.�ϲ����
	//����Ҫ�����Ϣ ����ΪNULL
	size_3 = width*height * 3 * sizeof(unsigned char);
	size_4 = width*height * 4 * sizeof(unsigned char);

	return S_OK;
}


void d3dClass::buildTexture(int framewidth, int frameheight)
{

	cuda_width = framewidth;
	cuda_height = frameheight;

	D3D10_TEXTURE2D_DESC desc;//1.���� texture desc
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = framewidth;  //2.����texture_desc����
	desc.Height = frameheight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;

	g_pd3dDevice->CreateTexture2D(&desc, NULL, &cuda_pTexture);//3.����texture ��ָ�븳ֵ//cuda_pTextrureָ������

	//ע��cuda����
	cudaGraphicsD3D10RegisterResource(&cudaResource, cuda_pTexture, cudaGraphicsRegisterFlagsNone);
}


void d3dClass::Render(unsigned char* cudaLinearMemory)
{
	
	cudaGraphicsMapResources(1, &cudaResource, 0);//map�������ݵ����� cuda�Ѿ�������� ȡ������

	//�ж� �Դ�û������
	cudaArray *cuArray;
	cudaGraphicsSubResourceGetMappedArray((cudaArray_t*)(&cuArray), cudaResource, 0, 0);
	cudaMemcpyToArray(cuArray, 0, 0, cudaLinearMemory, width*height* 4 * sizeof(unsigned char), cudaMemcpyDeviceToDevice);
	
	cudaGraphicsUnmapResources(1, &cudaResource, 0); ///unmap�ָ�d3dbufferʹ��Ȩ//!!


	//Clear the back buffer
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // red, green, blue, alpha
	g_pd3dDevice->ClearRenderTargetView(g_pRenderTargetView, ClearColor);//����ɫ
	

	//// Present our back buffer to our front buffer
	g_pd3dDevice->CopyResource(pBackBuffer, cuda_pTexture);//���back buffer cuda_pTexture��Ϊ����
	//���back buffer
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
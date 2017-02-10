
//! Include
#include "DrDevice.h"
#include "../../Utility/DrMainUtility.h"
#include "../ShaderResource/DrShaderResourceDesc.h"
#include "../ShaderResource/DrRenderTarget.h"

//! デバイス作成
DrBool DrDevice::CreateDevice(HWND hWnd, DrInt width, DrInt height)
{
	//! SwapChainの設定
	DrUint2 refreshRato;
	//リフレッシュレートの取得
	if (!GetRefreshRato(refreshRato, width, height))
		return DR_FALSE;
	DrSSwapChainDesc swapChainDesc(hWnd, width, height, refreshRato);


	//! Create Device & Context & SwapChain
	
	// ドライバの種類の列挙
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	DrUint numDriverTypes = ARRAYSIZE(driverTypes);

	// 機能レベルの列挙
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,	D3D_FEATURE_LEVEL_11_0,	D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,	D3D_FEATURE_LEVEL_9_3,	D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	DrUint numFeatureLevels = ARRAYSIZE(featureLevels);

	DrUint devCreateFlag = 0;// Device Create flag
	//	   devCreateFlag |= D3D11_CREATE_DEVICE_DEBUG;

	ID3D11DeviceContext * pDevContext;

	HRESULT hr;
	for (DrUint i = 0; i < numDriverTypes; ++i)
	{
		m_driverType = driverTypes[i];
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,           // ディスプレイデバイスのアダプタ（ＮＵＬＬの場合最初に見つかったアダプタ）
			m_driverType,      // デバイスドライバのタイプ
			nullptr,           // ソフトウェアラスタライザを使用する場合に指定する
			devCreateFlag,     // デバイスの生成フラグ
			featureLevels,     // 機能レベル
			numFeatureLevels,  // 機能レベル数
			D3D11_SDK_VERSION, // Dx11 バージョン
			&swapChainDesc,    // スワップチェインの設定
			&m_swapChain,      // IDXGIDwapChainインタフェース	
			&m_device,         // ID3D11Deviceインタフェース
			&m_featureLevel,    // サポートされている機能レベル
			&pDevContext);     // デバイスコンテキスト
		if (SUCCEEDED(hr))break;
	}
	if (FAILED(hr))
		return DR_FALSE;

	//! Create Context 
	m_deviceContext = DrNew(DrDeviceContext(this, pDevContext));
	DrRenderTarget* rtv = DrRenderTarget::CrateScreenRTV(*this);
	m_deviceContext->SetScreenRTV(rtv);

	DrDepthStencilView* depthStencil =
		DrDepthStencilView::CreateDSV("MainDepthStencil", *this, width, height);
	m_deviceContext->SetMainDepthStencil(depthStencil);

	m_deviceContext->ResetDrawCallCount();
	m_deviceContext->SetRT(0, rtv);
	m_deviceContext->ApplyRenderTargets();

	DrViewport viewport;
	viewport.Create(width, height);
	m_deviceContext->SetViewport(&viewport);

	LoadDefaultShader();

	return DR_TRUE;
}

//=============================================
// ! GetRefreshRato
// PC モニタのリフレッシュレートを取得
// @pram _out refreshRato x = 分子　y =分母
//            width & height 画面サイズ
// @return success is true
DrBool DrDevice::GetRefreshRato(__out DrUint2& refreshRato,
	const DrUint width, const DrUint height)
{
	refreshRato.x = 1;
	refreshRato.y = 60;
	//変数
	HRESULT	hr = S_OK;
	IDXGIFactory* factory;              // factory
	IDXGIAdapter* adapter;              // videocard
	IDXGIOutput* adapterOutput;         // monitor
	DrUint numModes;
	DXGI_MODE_DESC* displayModeList;

	// Create a DirectX graphics interface factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr)){ return DR_FALSE; }

	// use the factory to create an adpter for the primary graphics interface(video card)
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr)){ return DR_FALSE; }

	// enumerrate primary adapter output(monitor)
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr)){ return DR_FALSE; }

	// get the number of modes that fit the DXGI_FORMAT_R8G8B8_UNORM display format forthe adapter output(monitor)
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr)){ return DR_FALSE; }

	// create alist to hold all possible display modes for this monitor/video card combination
	displayModeList = DrNew(DXGI_MODE_DESC[numModes]);
	if (!displayModeList){ return DR_FALSE; }

	// now fill the display mode list structures
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr)){ return DR_FALSE; }

	// now go through all the display modes and find the one that matches the screen width and height
	// when a match is found store the numerator and denominator of the refresh rate for that monitor
	for (DrUint i = 0; i < numModes; i++){
		if (displayModeList[i].Width == width){
			if (displayModeList[i].Height == height){
				refreshRato.x = displayModeList[i].RefreshRate.Numerator;
				refreshRato.y = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DrDelete(displayModeList);
	DrSafeRelease(adapterOutput);
	DrSafeRelease(adapter);
	DrSafeRelease(factory);

	return DR_TRUE;
}

ID3D11Buffer* DrDevice::CreateBuffer(__in void * pData,
	__in size_t size,
	__in UINT cpuAct,
	__in UINT type)const
{
	HRESULT hr = E_FAIL;

	// バッファー リソース。
	D3D11_BUFFER_DESC BufferDesc;

	// サブリソース
	D3D11_SUBRESOURCE_DATA resource;

	D3D11_USAGE Usage = D3D11_USAGE_DEFAULT;

	if (cpuAct)
		Usage = D3D11_USAGE_DYNAMIC;
	else
		Usage = D3D11_USAGE_DEFAULT;

	if (pData)
	{
		resource.pSysMem = pData;
		resource.SysMemPitch = 0;
		resource.SysMemSlicePitch = 0;
	}

	// バッファの設定
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = size;                  // バッファサイズ
	BufferDesc.Usage = Usage;                     // リソース使用法を特定する
	BufferDesc.BindFlags = type;                  // バッファの種類
	BufferDesc.CPUAccessFlags = cpuAct;           // CPU アクセス
	BufferDesc.MiscFlags = 0;                     // その他のフラグも設定しない


	ID3D11Buffer* pBuffer;

	// バッファを作成する
	hr = GetDevD3D()->CreateBuffer(&BufferDesc, &resource, &pBuffer);

	if (FAILED(hr))
	{
		DrDebugLog("Create Buffer Error\n");
		return nullptr;
	}

	return pBuffer;

}

DrCBuffer* DrDevice::CreateCBuffer(__in void * pData,
	__in size_t size)const
{
	ID3D11Buffer* pBuffer = CreateBuffer(pData, size,
		D3D11_CPU_ACCESS_WRITE,
		D3D11_BIND_CONSTANT_BUFFER);
	if (pBuffer == nullptr)
	{
		DrDebugLog("Create Buffer Error\n");
		return nullptr;
	}
	DrCBuffer * pCBuffer = DrNew(DrCBuffer());
	pCBuffer->SetD3DBufferAndSize(pBuffer, size);

	return pCBuffer;
}

DrIndexBuffer* DrDevice::CreateIndexBuffer(__in void * pData,
	__in size_t size)const
{
	ID3D11Buffer* pBuffer = CreateBuffer(pData, size,
		0,
		D3D11_BIND_INDEX_BUFFER);
	DrIndexBuffer * pIB = DrNew(DrIndexBuffer());
	pIB->SetD3DBufferAndSize(pBuffer, size);

	return pIB;
}

DrSamplerState* DrDevice::CreateSamplerState(const D3D11_SAMPLER_DESC& desc)
{
	ID3D11SamplerState * pSampler;
	m_device->CreateSamplerState(&desc, &pSampler);
	if (pSampler)
	{
		DrSamplerState * pDrSampler = DrNew(DrSamplerState);
		pDrSampler->SetD3DSamplerState(pSampler);
		return pDrSampler;
	}
	return nullptr;
}

DrVertexBuffer* DrDevice::CreateVertexBuffer(__in void * pData,
	__in size_t size,
	size_t stride,
	DrUint offset)const
{
	ID3D11Buffer* pBuffer = CreateBuffer(pData, size,
		0,
		D3D11_BIND_VERTEX_BUFFER);
	DrVertexBuffer * pVB = DrNew(DrVertexBuffer());
	pVB->SetD3DBufferAndSize(pBuffer, size);
	pVB->SetStride(stride);
	pVB->SetOffset(offset);

	return pVB;
}

DrBool DrDevice::LoadDefaultShader()
{
	if (m_device == nullptr)
		return DR_FALSE;

	DrVertexShader * pSSDefaultVS = DrNew(DrVertexShader);

	pSSDefaultVS->LoadFromCSO(m_device, (DRUT::Resource::GetCSODirectory() + "DrSSDefaultVS.cso").c_str());

	return DR_TRUE;
}

DrBool DrDevice::Flip()
{
	if (m_device && m_swapChain)
		m_swapChain->Present(1, 0);
	else
		return DR_FALSE;
	return DR_TRUE;
}

#pragma region //! 終了処理
void DrDevice::UnInit()
{
	DrSafeDelete(m_deviceContext);
	DrSafeRelease(m_swapChain);
	DrSafeRelease(m_device);
}

DrDevice::~DrDevice()
{
	UnInit();
}

#pragma endregion
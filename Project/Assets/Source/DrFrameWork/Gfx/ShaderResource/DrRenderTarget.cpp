
//! Include 
#include "DrRenderTarget.h"
#include "../Device/DrDevice.h"
#include "DrShaderResourceDesc.h"

//error macro
#define RTV_CREATE_ERR_TO_RETURN	\
if (FAILED(hr))\
		{\
		DrDebugLog("Create RenderTarget Failed \n"); \
		return DR_FALSE; \
		}

//! �O����`
DR_INSTANTIATE_NAMEDLIST( DrRenderTarget );

//! DrRenderTarget Method

#pragma region //! protected Method

//! �R���X�g���N�^
DrRenderTarget::DrRenderTarget() :m_rtv(nullptr){};
//! RenderTarget�̉��
void DrRenderTarget::UnInit()
{
	DrSafeRelease(m_rtv);
	DrSafeRelease(m_srv);
	DrSafeRelease(m_tex2d);
}

//! RenderTarget�̏�����
DrBool DrRenderTarget::Create(const DrDevice& dev,
	const DrInt width,
	const DrInt height,
	DXGI_FORMAT format /*= DXGI_FORMAT_R8G8B8A8_UNORM*/)
{
	//! ������
	UnInit();

	ID3D11Device* pDev = dev.GetDevD3D();

	//! Step 1 Create Texture
	{
		DR_TEX2D_DESC texDesc(width, height, format);
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		HRESULT hr = pDev->CreateTexture2D(&texDesc, nullptr, &m_tex2d);
		RTV_CREATE_ERR_TO_RETURN;
	}

	//! Step 2 Create Render Target View
	{
		HRESULT hr = pDev->CreateRenderTargetView(m_tex2d, nullptr, &m_rtv);
		RTV_CREATE_ERR_TO_RETURN;
	}
	//! Step 3 Create Shader Resource View
	{
		HRESULT hr = pDev->CreateShaderResourceView(m_tex2d, nullptr, &m_srv);
		RTV_CREATE_ERR_TO_RETURN;
	}

	m_rtvSize = DrInt2(width, height);

	return DR_TRUE;
}

#pragma endregion

//! �f�X�g���N�^
DrRenderTarget::~DrRenderTarget()
{
	UnInit();
}

//! RTV�̃T�C�Y���擾
DrInt2 DrRenderTarget::GetRTVSize()const
{
	return m_rtvSize;
}

//! ��ʂɉf��RTV���쐬
DrRenderTarget* DrRenderTarget::CrateScreenRTV(const DrDevice& dev)
{
	ID3D11Device * pDev = dev.GetDevD3D();
	IDXGISwapChain * pSC = dev.GetSC();

	// Swap Chain ����@�o�b�N�o�b�t�@�ւ̃|�C���^���擾
	ID3D11Texture2D* pBackBuffer = NULL;
	ID3D11RenderTargetView* pD3Drtv;
	HRESULT hr = pSC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	RTV_CREATE_ERR_TO_RETURN;

	// �o�b�N�o�b�t�@�ւ̃|�C���^���w�肵��RTV���쐬
	hr = pDev->CreateRenderTargetView(pBackBuffer, NULL, &pD3Drtv);
	D3D11_TEXTURE2D_DESC desc;
	pBackBuffer->GetDesc(&desc);

	DrRenderTarget* rtv = new DrRenderTarget();
	rtv->SetName("ScreenRenderTargetView");
	rtv->m_rtv = pD3Drtv;
	rtv->m_rtvSize.x = desc.Width;
	rtv->m_rtvSize.y = desc.Height;

	DrSafeRelease(pBackBuffer);
	RTV_CREATE_ERR_TO_RETURN;
	return rtv;
}

//! RTV���쐬
DrRenderTarget* DrRenderTarget::CreateRTV(DrString name,
	const DrDevice& dev,
	const DrInt width,
	const DrInt height,
	DXGI_FORMAT format)
{
	DrRenderTarget * rtv = DrNew(DrRenderTarget);
	DrBool succed = rtv->Create(dev, width, height, format);
	rtv->SetName(name);

	if (!succed)
	{
		DrSafeDelete(rtv);
		return nullptr;
	}
	return rtv;
}

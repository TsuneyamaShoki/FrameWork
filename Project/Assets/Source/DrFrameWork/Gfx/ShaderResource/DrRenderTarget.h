
#pragma once

//! Include
#include "../../Utility/DrInterfaceUtility.h"
#include "DrTexture.h"

class DrDevice;

//! [class] 
class DrRenderTarget :public DrTexture2D, 
	public IDrStaticNamedList<DrRenderTarget>
{
private:
	ID3D11RenderTargetView*	  m_rtv;
	DrInt2                    m_rtvSize;
protected:
	//! Copy�֎~
	void operator = (DrRenderTarget*) = delete;
	DrRenderTarget(const DrRenderTarget&) = delete;

	//! �R���X�g���N�^
	DrRenderTarget();

	//! �쐬
	DrBool Create(const DrDevice& dev,
		const DrInt width,
		const DrInt height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
	//! ���
	void UnInit();
public:
	virtual ~DrRenderTarget();

	ID3D11RenderTargetView* GetRTV(){ return m_rtv; }
	DrInt2 GetRTVSize()const;

	//! failed is nullptr
	static DrRenderTarget* CrateScreenRTV(const DrDevice& dev);
	static DrRenderTarget* CreateRTV(DrString name,
		const DrDevice& dev,
		const DrInt width,
		const DrInt height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

};
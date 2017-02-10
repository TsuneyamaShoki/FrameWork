
#pragma once

//! Include 
#include "../../Utility/DrMainUtility.h"
#include <d3d11.h>


#pragma region //! Prototype

class DrDevice;
class DrDeviceContext;
class DrTexture;
class DrRenderTarget;

class DrCBuffer;
class DrIndexBuffer;
class DrVertexBuffer;
class DrSamplerState;

class DrRasterizerState;
class DrDepthStencilState;

#pragma endregion

//! [class] IDrDevice	Dx11 Device Intarface
class IDrDevice
{
public:
	//get device contetxt
	virtual DrDeviceContext* GetDC()const = 0;
	virtual ID3D11Device*    GetDevD3D()const = 0;
	virtual IDXGISwapChain*	 GetSC()const = 0;
};

//! [class] DrDevice	Dx11 Device
class DrDevice : IDrDevice
{
#pragma region //private

private:
	ID3D11Device*       m_device;
	IDXGISwapChain*     m_swapChain;
	D3D_DRIVER_TYPE     m_driverType;
	D3D_FEATURE_LEVEL   m_featureLevel;
	DrDeviceContext*    m_deviceContext;


	// ! GetRefreshRato
	// PC モニタのリフレッシュレートを取得
	// @pram _out refreshRato x = 分子　y =分母
	//            上記の引数は戻り値として扱う。
	//            width & height 画面サイズ
	// @return true is success
	DrBool GetRefreshRato(__out DrUint2& refreshRato, const DrUint width, const DrUint height);

	DrBool LoadDefaultShader();
#pragma endregion

public:
	
	virtual ~DrDevice();

	void UnInit();

	//=============================================
	// ! CreateDevice
	// Create DirectX Device & SwapChain & DeviceContext
	//
	// @pram    hWnd	DirectXの描画ターゲットウィンドウハンドル
	//          width & height Back Buffer Size
	// @return true is success
	DrBool CreateDevice(HWND hWnd, DrInt width, DrInt height);


	//todo
	DrTexture*          CreateTextureFromFile(DrString name);
	DrRenderTarget*     CreateRenderTarget(DrString name);

//	//todo CreateShaders
//	DrVertexShader*     CreateVSFromCSO(DrString filename);
//	DrPixelShader*      CreatePSFromCSO(DrString filename);
//	DrGeometryShader*   CreateGSFromCSO(DrString filename);
//	DrHullShader*       CreateHSFromCSO(DrString filename);
//	DrComputeShader*    CreateCSFromCSO(DrString filename);
//	DrDomainShader*     CreateDSFromCSO(DrString filename);

	DrSamplerState* CreateSamplerState(const D3D11_SAMPLER_DESC& desc);

	DrCBuffer* CreateCBuffer(__in void * pData,
		__in size_t size)const;

	ID3D11Buffer*	CreateBuffer(__in void * pData,
		__in size_t size,
		__in UINT cpuAct,
		__in UINT type)const;

	DrBool Flip();

	DrIndexBuffer* CreateIndexBuffer(void* pData, size_t size)const;
	DrVertexBuffer* CreateVertexBuffer(void* pData, size_t size, size_t stride, DrUint offset = 0)const;

	//! Get DeviceContext
	DrDeviceContext*    GetDC()const override { return m_deviceContext; }
	//! Get DirectX Device Pointer
	ID3D11Device*       GetDevD3D()const override{ return m_device; }
	//! Get DirectX Swap Chain
	IDXGISwapChain*	    GetSC()const override{ return m_swapChain; }
};
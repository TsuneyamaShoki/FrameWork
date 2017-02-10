
#pragma once

//! Include
#include <d3d11.h>
#include "../../Utility/DrMainUtility.h"
//dx11 multi sample desc.
struct DR_SAMPLE_DESC : DXGI_SAMPLE_DESC
{
	DR_SAMPLE_DESC(DrInt count = 1, DrInt quality = 0)
	{
		Count = (DrUint)count;
		Quality = (DrUint)quality;
	}
};

struct DR_MODE_DESC : DXGI_MODE_DESC
{
	DR_MODE_DESC(DrUint width,
	DrUint height,
	DrInt2 refreshRato,
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM,
	DXGI_MODE_SCANLINE_ORDER scanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
	DXGI_MODE_SCALING  scaling = DXGI_MODE_SCALING_UNSPECIFIED)
	{
		Width = width;                          // �o�b�N�o�b�t�@�̕�
		Height = height;                        // �o�b�N�o�b�t�@�̍���
		Format = format;                        // �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B �͈͂O�D�O����P�D�O)
		RefreshRate.Numerator = refreshRato.x;  // ���t���b�V�����[�g�i����j
		RefreshRate.Denominator = refreshRato.y;// ���t���b�V�����[�g�i���q�j
		ScanlineOrdering = scanlineOrdering;
		Scaling = scaling;
	}
};

// dx11 swapchain desc
struct DrSSwapChainDesc : DXGI_SWAP_CHAIN_DESC
{
	//todo
	DrSSwapChainDesc(HWND hWnd,
	DrUint width,
	DrUint height,
	DrInt2 refreshRato,
	DrBool isFullScreen = DR_FALSE)
	{
		BufferCount = 1;                                            // �o�b�N�o�b�t�@�̐�
		BufferDesc = DR_MODE_DESC(width, height, refreshRato);
		BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;              // �o�b�N�o�b�t�@�̎g�p���@
		OutputWindow = hWnd;                                        // �֘A�t����E�C���h�E
		SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SampleDesc = DR_SAMPLE_DESC();
		Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		Windowed = !isFullScreen;
	}
};
// dx11 sampler desc.
struct DR_SAMPLER_DESC : D3D11_SAMPLER_DESC
{
	//todo
};

// dx11 buffer desc.
struct DR_BUFFER_DESC : D3D11_BUFFER_DESC
{
	//todo
};

struct DR_DEPTH_STENCIL_DESC : D3D11_DEPTH_STENCIL_DESC
{
	DR_DEPTH_STENCIL_DESC()
	{
		ZeroMemory(this, sizeof(DR_DEPTH_STENCIL_DESC));
		DepthEnable = DR_TRUE;
		DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DepthFunc = D3D11_COMPARISON_LESS;

		// set up the description of the stencl state
		StencilEnable = DR_TRUE;
		StencilReadMask = 0xFF;
		StencilWriteMask = 0xFF;

		// stencil operation if pixel is front-facing
		FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// stencil operation if pixel is�@back-facing
		BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	}
};

struct DR_SRV_DESC : D3D11_SHADER_RESOURCE_VIEW_DESC
{
	DR_SRV_DESC(DXGI_FORMAT format)
	{
		ZeroMemory(this, sizeof(DR_SRV_DESC));
		Format = format;
		ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	}
};

// dx11 rtv desc
struct DR_RTV_DESC : D3D11_RENDER_TARGET_VIEW_DESC
{
	DR_RTV_DESC(DXGI_FORMAT format)
	{
		Format = format;
		ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		Buffer.FirstElement = 0;
		Buffer.ElementOffset = 0;

		Texture1D.MipSlice = 0;
		Texture2D.MipSlice = 0;
		Texture3D.MipSlice = 0;

		Texture2DMS.UnusedField_NothingToDefine = 0;

		Texture1DArray.ArraySize = 0;
		Texture1DArray.FirstArraySlice = 0;
		Texture1DArray.MipSlice = 0;

		Texture2DArray.ArraySize = 0;
		Texture2DArray.FirstArraySlice = 0;
		Texture2DArray.MipSlice = 0;

		Texture2DMSArray.ArraySize = 0;
		Texture2DMSArray.FirstArraySlice = 0;
	}
};

// dx11 texture desc.
struct DR_TEX2D_DESC : D3D11_TEXTURE2D_DESC
{
	DR_TEX2D_DESC(DrUint width,
	DrUint height,
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM,
	D3D11_BIND_FLAG bindflg = D3D11_BIND_SHADER_RESOURCE,
	DrUint cpuAccess = 0,
	D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
	DrUint mipmapLevel = 1,
	DR_SAMPLE_DESC sample = DR_SAMPLE_DESC(),
	DrUint miscflg = 0,
	DrUint arraySize = 1
	)
	{
		Width = width;
		Height = height;
		BindFlags = bindflg;
		Format = format;
		CPUAccessFlags = cpuAccess;
		Usage = usage;
		MipLevels = mipmapLevel;
		SampleDesc = sample;
		MiscFlags = miscflg;
		ArraySize = arraySize;
	}
};
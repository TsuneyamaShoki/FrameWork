
#pragma once

//! Include
#include "../../Utility/DrMainUtility.h"
#include <d3d11.h>

class DrBuffer : public DrNamed
{
private:
	ID3D11Buffer* m_buffer;
	void* m_originData;
	DrUint m_bufferSize;
public:
	DrBuffer() :
		m_buffer(nullptr),
		m_originData(nullptr),
		m_bufferSize(0){};
	virtual ~DrBuffer()
	{
		DrSafeDelete(m_originData);
		DrSafeRelease(m_buffer);
	}

	//=============================================
	// ! GetBuffer
	// Dx11　形式でバッファポインタを取得
	// @return true is success
	ID3D11Buffer* GetBuffer()const{ return m_buffer; };

	//=============================================
	// ! Create
	// Create DirectX Device & SwapChain & DeviceContext
	// @pram buffer	デバイス作成した元になるバッファデータ
	// @return true is success
	DrBool SetD3DBufferAndSize(ID3D11Buffer* buffer, DrUint size)
	{
		m_buffer = buffer;
		m_bufferSize = size;
		return TRUE;
	};

	DrBool SetOriginData(void* pOriginData)
	{
		m_originData = pOriginData;
		return DR_TRUE;
	}

	void* GetOriginData()
	{
		return m_originData;
	}

	//! Get Size
	DrUint GetBufferSize()const{ return m_bufferSize; }
};

//! Include
#include "DrShader.h"
#include "../../Utility/DrMainUtility.h"
#include <d3d11shader.h>
#include <d3dcompiler.h>

//! static変数定義
DR_INSTANTIATE_NAMEDLIST(DrVertexShader);
DR_INSTANTIATE_NAMEDLIST(DrPixelShader);
DR_INSTANTIATE_NAMEDLIST(DrGeometryShader);
DR_INSTANTIATE_NAMEDLIST(DrHullShader);
DR_INSTANTIATE_NAMEDLIST(DrDomainShader);
DR_INSTANTIATE_NAMEDLIST(DrComputeShader);

template class DrShader<ID3D11VertexShader>;
template class DrShader<ID3D11PixelShader>;
template class DrShader<ID3D11GeometryShader>;
template class DrShader<ID3D11HullShader>;
template class DrShader<ID3D11DomainShader>;
template class DrShader<ID3D11ComputeShader>;

//! Constructor
template<typename T>
DrShader<T>::DrShader() :m_shader(nullptr),m_inputLayout(nullptr)
{
	this->DrBinary::DrBinary();
}

//! Destructor
template<typename T>
DrShader<T>::~DrShader()
{
	DrSafeRelease(m_shader);
	DrSafeRelease(m_inputLayout);
};

//! Compile file
template<typename T>
DrBool DrShader<T>::CompileFromFile(
	 ID3D11Device* pDev,
	 const DrLChar* filename,
	 const DrChar*  entryPoint,
	 const DrChar*  pProfile)
{
	ID3D10Blob* pBlob = nullptr;
	ID3D10Blob* error = nullptr;

	//! 行列を列優先で設定し、古い形式の記述を許可しないようにする
	DrUint Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
	//! 最適化レベルを設定する
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	//! ファイルを元にエフェクトをコンパイルする
	D3DCompileFromFile(filename,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		pProfile,
		Flag1,
		0,
		&pBlob,
		&error);

	if (error)
	{
		//! ToDo: Debugログ掃き出し  "File Read Error"filename (DrChar*)error->GetBufferPointer()
		return DR_FALSE;
	}

	if (pBlob == nullptr)
	{
		//! ToDo: Debugログ掃き出し  "File Read Error"filename
		return DR_FALSE;
	}


	m_size = pBlob->GetBufferSize();
	m_bin = DrNew(DrByte[m_size]);

	CopyMemory(m_bin, pBlob->GetBufferPointer(), m_size);
	DrSafeRelease(pBlob);

	CompileFromMemory(pDev, m_bin, m_size);
	return DR_TRUE;
};

//! Load Shader Binary
template<typename T>
DrBool DrShader<T>::LoadFromCSO(ID3D11Device* pd3dDevice, const DrChar* filename)
{
	if (pd3dDevice == nullptr)
		return DR_FALSE;

	DrBool isSuccess = DrBinary::Load(filename);

	if (!isSuccess)
		return DR_FALSE;

	isSuccess = CompileFromMemory(pd3dDevice, m_bin, m_size);

	if (!isSuccess)
		return DR_FALSE;
	
	//! ToDo: Debugログ掃き出し  "Load Success "filename
	DrDebugLog("Load Success -> \"%s\"\n", filename);

	DrString name = DRUT::PassToFileName(filename);
	name = name.substr(0, name.rfind('.'));
	SetName(name);
	//	AddObject( this );
	return DR_TRUE;
}

//! Compile Vertex Shader
template<>
DrBool DrVertexShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz)
{
	if (pDev == nullptr) return DR_FALSE;
	HRESULT hr = pDev->CreateVertexShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return DR_FALSE;
	if (CreateInputLayout(pDev) == DR_FALSE)
		return DR_FALSE;
	return DR_TRUE;
}

//! Compile Pixel Shader
template<>
DrBool DrPixelShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz)
{
	if (pDev == nullptr) return DR_FALSE;
	HRESULT hr = pDev->CreatePixelShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return DR_FALSE;
	return DR_TRUE;
}

//! Compile Hull Shader
template<>
DrBool DrHullShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz)
{
	if (pDev == nullptr) return DR_FALSE;
	HRESULT hr = pDev->CreateHullShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return DR_FALSE;
	return DR_TRUE;
}

//! Compile Geometry Shader 
template<>
DrBool DrGeometryShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz)
{
	if (pDev == nullptr) return DR_FALSE;
	HRESULT hr = pDev->CreateGeometryShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return DR_FALSE;
	return DR_TRUE;
}

//! Compile Compute Shader
template<>
DrBool DrComputeShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz)
{
	if (pDev == nullptr) return DR_FALSE;
	HRESULT hr = pDev->CreateComputeShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return DR_FALSE;
	return DR_TRUE;
}

//! Compile Domain Shader
template<>
DrBool DrDomainShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz)
{
	if (pDev == nullptr) return DR_FALSE;
	HRESULT hr = pDev->CreateDomainShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return DR_FALSE;
	return DR_TRUE;
}

//! Create Auto Input Layout 
template<>
DrBool DrVertexShader::CreateInputLayout(ID3D11Device* pDev)
{
	//! step01 コンパイル済み頂点シェーダからメタデータの取得
	ID3D11ShaderReflection* pVertexShaderReflection = nullptr;
	if (FAILED(D3DReflect(m_bin,
		m_size,
		IID_ID3D11ShaderReflection,
		(void**)&pVertexShaderReflection)))
	{
		//! Todo DebugLog"Reflect Error"
		return DR_FALSE;
	}

	//! step02 メタデータからDescを取得
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	//! step03 DescからInputLayoutを生成するためのデータを構築
	DrVector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (DrUint i = 0; i< shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		//switch - case 見やすくするため省略
		enum
		{
			F32 = D3D_REGISTER_COMPONENT_FLOAT32,
			S32 = D3D_REGISTER_COMPONENT_SINT32,
			U32 = D3D_REGISTER_COMPONENT_UINT32,
		};
		switch (paramDesc.Mask)
		{
		case 1://! 1Dデータ
			switch (paramDesc.ComponentType)
			{
			case U32:elementDesc.Format = DXGI_FORMAT_R32_UINT; break;
			case S32:elementDesc.Format = DXGI_FORMAT_R32_SINT; break;
			case F32:elementDesc.Format = DXGI_FORMAT_R32_FLOAT; break;
			}
			break;
		case 3://! 2Dデータ
			switch (paramDesc.ComponentType)
			{
			case U32:elementDesc.Format = DXGI_FORMAT_R32G32_UINT; break;
			case S32:elementDesc.Format = DXGI_FORMAT_R32G32_SINT; break;
			case F32:elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT; break;
			}
			break;
		case 7://! 3Dデータ
			switch (paramDesc.ComponentType)
			{
			case U32:elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT; break;
			case S32:elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT; break;
			case F32:elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; break;
			}
			break;
		case 15://! 4Dデータ
			switch (paramDesc.ComponentType)
			{
			case U32:elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT; break;
			case S32:elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT; break;
			case F32:elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
			}
			break;
		}

		inputLayoutDesc.push_back(elementDesc);
	}

	//! step04 DescからInputLayoutを構築
	HRESULT hr = pDev->CreateInputLayout(&inputLayoutDesc[0],
		inputLayoutDesc.size(),
		m_bin,
		m_size,
		&m_inputLayout);

	DrSafeRelease(pVertexShaderReflection);
	if (FAILED(hr))
	{
		//! Todo DebugLog"D3D11Device->CreateInputLayout Error"
		return DR_FALSE;
	}
	return DR_TRUE;
}

template<typename T>
DrBool DrShader<T>::CreateInputLayout(ID3D11Device* pDev)
{
	return DR_FALSE;
}
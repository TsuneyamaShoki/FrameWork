
#pragma once

//! Include 
#include "../../Utility/DrInterfaceUtility.h"
#include "../../Utility/DrMainUtility.h"
#include <d3d11.h>

//! ‘O•û’è‹`


//! [Class] DrShader : Inheritance
template <typename Shader>
class DrShader : public DrBinary , public IDrStaticNamedList<DrShader<Shader>>
{
protected:
	Shader* m_shader;
	ID3D11InputLayout* m_inputLayout;
public:
	DrShader();
	virtual ~DrShader();

	inline DrBool CompileFromFile( ID3D11Device* pDev,
		 const DrLChar* filename,
		 const DrChar* entryPoint,
		 const DrChar* pProfile);

	inline DrBool LoadFromCSO( ID3D11Device * pDev, const DrChar* filename);

	inline DrBool CompileFromMemory(ID3D11Device* pDev, void* memory, size_t size);

	inline DrBool CreateInputLayout(ID3D11Device* pDev);

	ID3D11InputLayout* GetInputLayout()const{ return m_inputLayout; }
	Shader* GetShader()const { return m_shader; }
};

//! typedef
typedef DrShader<ID3D11VertexShader>    DrVertexShader;
typedef DrShader<ID3D11PixelShader>     DrPixelShader;
typedef DrShader<ID3D11GeometryShader>  DrGeometryShader;
typedef DrShader<ID3D11HullShader>      DrHullShader;
typedef DrShader<ID3D11DomainShader>    DrDomainShader;
typedef DrShader<ID3D11ComputeShader>   DrComputeShader;

//! extern template  "DrShader.cpp"
extern template class DrShader<ID3D11VertexShader>;
extern template class DrShader<ID3D11PixelShader>;
extern template class DrShader<ID3D11GeometryShader>;
extern template class DrShader<ID3D11HullShader>;
extern template class DrShader<ID3D11DomainShader>;
extern template class DrShader<ID3D11ComputeShader>;
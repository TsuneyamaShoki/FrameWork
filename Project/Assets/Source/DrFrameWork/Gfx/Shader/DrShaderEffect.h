
#pragma once

//! Include
#include "../../Utility/DrInterfaceUtility.h"
#include "../../Utility/DrMainUtility.h"
#include <d3d11.h>

//! ‘O•û’è‹`
class DrVertexShader;
class DrPixelShader;
class DrGeometryShader;
class DrHullShader;
class DrDomainShader;
class DrComputeShader;
class DrDepthStencilState;
class DrRasterizerState;
class DrBlendState;
class DrDevice;

//[Class] DrDrShaderEffect
class DrShaderEffect : public DrNamed,
						 public IDrStaticNamedList<DrShaderEffect>
{
private:
#pragma region //protected:
protected:
	DrVertexShader* m_vertexShader;
	DrPixelShader* m_pPixelShader;
	DrGeometryShader* m_pGeometoryShader;
	DrHullShader* m_pHullShader;
	DrDomainShader* m_pDomainShader;
	DrComputeShader* m_pComputeShader;

	DrDepthStencilState* m_pDepthStencilState;
	DrRasterizerState* m_pRasterizerState;
	DrBlendState* m_pBlensState;
#pragma endregion
public:

	DrBool LoadPackageFromXml(DrDevice* pDev, const DrString& file);
	
	DrShaderEffect();
	virtual ~DrShaderEffect();

	//! Getter
	ID3D11InputLayout*  GetInputLayout();
	DrVertexShader*     GetVertexShader() const{ return m_vertexShader; }
	DrPixelShader*      GetPixelShader()const{ return m_pPixelShader; }
	DrGeometryShader*   GetGeometryShader()const{ return m_pGeometoryShader; }
	DrHullShader*       GetHullShader()const{ return m_pHullShader; }
	DrDomainShader*     GetDomainShader()const{ return m_pDomainShader; }
	DrComputeShader*    GetComputeShader()const{ return m_pComputeShader; }
	DrRasterizerState*   GetRasterizeState()      { return m_pRasterizerState; }
	DrDepthStencilState* GetDepthStencilState(){ return m_pDepthStencilState; }
	DrBlendState*        GetBlendState(){ return m_pBlensState; };

	//! Setter
	DrBool SetVertexShader(DrVertexShader*);
	DrBool SetPixelShader(DrPixelShader*);
	DrBool SetGeometryShader(DrGeometryShader*);
	DrBool SetHullShader(DrHullShader*);
	DrBool SetDomainShader(DrDomainShader*);
	DrBool SetComputeShader(DrComputeShader*);
};

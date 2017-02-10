
#pragma once

//! Include
#include "../../Utility/DrInterfaceUtility.h"
#include "../Shader/DrShaderUtility.h"
#include <d3d11.h>

//! classDefine
class DrRenderTarget;
class DrDepthStencilView;
class DrBlendState;
class DrTexture;
class DrShaderEffect;
class DrBuffer;
class DrCBuffer;
class DrViewport;
class DrCamera;
class DrDevice;
class DrRasterizerState;
class DrDepthStencilState;

//! [Class] DrDeviceContext
class DrDeviceContext
{
public:
	static const DrInt MAX_RTs = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
#pragma region //private:
private:
	DrDevice*                              m_pDevice;
	ID3D11DeviceContext*                   m_pDeviceContext;
	DrShaderEffect*                        m_bindShaderEffect;
	DrBool                                 m_activeShaders[DR_SHADER_INDEX::SHADER_MAX_IDX];
	DrRenderTarget *                       m_renderTarget[MAX_RTs];
	DrRenderTarget *                       m_mainRenderTarget;
	DrDepthStencilView *                   m_mainDepthStencil;
	DrDepthStencilView *                   m_depthStencil;

	DrBlendState*                          m_pBlendState;
	DrRasterizerState *                    m_pRasterizerState;
	DrDepthStencilState*                   m_pDepthStencilState;

	DrCamera*                              m_mainCamera;
	DrInt                                  m_drawCallCount;
#pragma endregion
protected:
public:
		DrDeviceContext();
	virtual ~DrDeviceContext();
};

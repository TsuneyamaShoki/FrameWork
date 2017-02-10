
#pragma once

//! Include
#include "../../Utility/DrMainUtility.h"
#include <d3d11.h>

class DrDevice;

//! BlendMode
enum class DR_BLEND_MODE
{
	NONE = 0,
	ALPHA_BLEND = 1,
	ADD = 2,
	SUBTRACT = 3,
};


//! Convert Blend Mode from String
static DR_BLEND_MODE ConvertBlendModeFromString(const char* str)
{
	if (str == "NONE")
		return DR_BLEND_MODE::NONE;
	if (str == "ALPHA_BLEND")
		return DR_BLEND_MODE::ALPHA_BLEND;
	if (str == "ADD")
		return DR_BLEND_MODE::ADD;
	if (str == "SUBTRACT")
		return DR_BLEND_MODE::SUBTRACT;

	return DR_BLEND_MODE::NONE;
}

// ! Blend State
class DrBlendState
{
private:
	ID3D11BlendState* m_pD3DBlendState;
public:
	DrBlendState();
	virtual ~DrBlendState();
	DrBool CreateBlendState(DrDevice* pDev, DR_BLEND_MODE bolenMode);

	ID3D11BlendState*  GetBlendState()const
	{
		return m_pD3DBlendState;
	}
};
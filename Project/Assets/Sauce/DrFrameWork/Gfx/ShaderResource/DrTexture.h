
#pragma once

#include <d3d11.h>
#include "DrRegisterObject.h"

//! [Class] DrTexture : テクスチャの基底クラス
class DrTexture : public DrRegisterResource,
				  public DrNamed
{
protected:
	ID3D11ShaderResourceView * m_srv;
	DrBool m_isAlpha = DR_FALSE;
public:
	DrTexture() : DrRegisterResource(), m_srv(nullptr){};

	DrBool SetSRV(ID3D11ShaderResourceView*srv)
	{
		if (m_srv)
			return DR_FALSE;
		m_srv = srv;
		return DR_TRUE;
	}
	DrBool SetAlphaMode(DrBool flag)
	{
		m_isAlpha = flag;
		return DR_TRUE;
	}

	//! Getter
	DrBool IsAlpha()const
	{
		return m_isAlpha;
	}
	ID3D11ShaderResourceView * GetSRV()const
	{
		return m_srv;
	}

	virtual ~DrTexture()
	{
		DrSafeRelease(m_srv);
	}
};

//! [Class] DrTexture1D : DrTexture
class DrTexture1D : public DrTexture
{
protected:
	ID3D11Texture1D * m_tex1d;
public:
	DrTexture1D() :DrTexture(){};

	virtual ~DrTexture1D()
	{
		DrSafeRelease(m_tex1d);
	};
};

//! [Class] DrTexture2D : DrTexture
class DrTexture2D : public DrTexture
{
protected:
	ID3D11Texture2D * m_tex2d;
public:
	DrTexture2D() :DrTexture(){};

	virtual ~DrTexture2D()
	{
		DrSafeRelease(m_tex2d);
	};
};

//! [Class] DrTexture3D : DrTexture
class DrTexture3D : public DrTexture
{
protected:
	ID3D11Texture3D * m_tex3d;
public:
	DrTexture3D() :DrTexture(){};

	virtual ~DrTexture3D()
	{
		DrSafeRelease(m_tex3d);
	};
};

//
//#include "DrDeviceContext.h"
//
////! Constructor
//DrDeviceContext::DrDeviceContext(DrDevice* pDev, ID3D11DeviceContext* pCotext)
//:m_pDeviceContext(pCotext),
//m_bindShaderEffect(nullptr),
//m_mainCamera(nullptr)
//{
//	m_pDevice = pDev;
//	m_mainDepthStencil = nullptr;
//	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//};
//
////! Destructor
//DrDeviceContext::~DrDeviceContext()
//{
//	DrSafeDelete(m_mainRenderTarget);
//	DrSafeDelete(m_mainDepthStencil);
//	DrSafeRelease(m_pDeviceContext);
//}
//
////! clear color & depth buffer
//void DrDeviceContext::Clear(DrFloat4& color /* 0x~~~~~~ */)
//{
//	if (m_pDeviceContext)
//	{
//		//! crear rendertargets
//		for (int i = 0; i < MAX_RDr; ++i)
//		{
//			if (m_renderTarget[i])
//				m_pDeviceContext->ClearRenderTargetView(m_renderTarget[i]->GetRTV(), &color[0]);
//		}
//
//		//! crear depth stencil view
//		if (m_depthStencil)
//			m_pDeviceContext->ClearDepthStencilView(m_depthStencil->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//	}
//}
//
////! Set texture
//DrBool DrDeviceContext::SetTexture(DrInt slotIndex,
//	const DrTexture* texture,
//	DR_SHADER_TYPE type)
//{
//	if (m_pDeviceContext == nullptr) return DR_FALSE;
//
//	//! Shader Resource View の取得
//	ID3D11ShaderResourceView* srv = nullptr;
//	if (texture != nullptr)
//		srv = texture->GetSRV();
//	else
//		return DR_FALSE;
//
//	// テクスチャをgpuに設定
//	switch (type)
//	{
//	case VERTEX_SHADER:		m_pDeviceContext->VSSetShaderResources(slotIndex, 1, &srv); break;
//	case PIXEL_SHADER:		m_pDeviceContext->PSSetShaderResources(slotIndex, 1, &srv); break;
//	case GEOMETRY_SHADER:	m_pDeviceContext->GSSetShaderResources(slotIndex, 1, &srv); break;
//	case HULL_SHADER:		m_pDeviceContext->HSSetShaderResources(slotIndex, 1, &srv); break;
//	case DOMAIN_SHADER:		m_pDeviceContext->DSSetShaderResources(slotIndex, 1, &srv); break;
//	case COMPUTE_SHADER:	m_pDeviceContext->CSSetShaderResources(slotIndex, 1, &srv);	break;
//	default:
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::SetSamplerState(DrSamplerState * pSamler,
//	DrInt registerIndex,
//	DR_SHADER_TYPE ShaderType)
//{
//	if (m_pDeviceContext == nullptr) return DR_FALSE;
//
//	//! Shader Resource View の取得
//	ID3D11SamplerState* pD3DSampler = nullptr;
//	if (pSamler != nullptr)
//		pD3DSampler = pSamler->GetSamplerState();
//	else
//		return DR_FALSE;
//
//	// テクスチャをgpuに設定
//	switch (ShaderType)
//	{
//	case VERTEX_SHADER:		m_pDeviceContext->VSSetSamplers(registerIndex, 1, &pD3DSampler); break;
//	case PIXEL_SHADER:		m_pDeviceContext->PSSetSamplers(registerIndex, 1, &pD3DSampler); break;
//	case GEOMETRY_SHADER:	m_pDeviceContext->GSSetSamplers(registerIndex, 1, &pD3DSampler); break;
//	case HULL_SHADER:		m_pDeviceContext->HSSetSamplers(registerIndex, 1, &pD3DSampler); break;
//	case DOMAIN_SHADER:		m_pDeviceContext->DSSetSamplers(registerIndex, 1, &pD3DSampler); break;
//	case COMPUTE_SHADER:	m_pDeviceContext->CSSetSamplers(registerIndex, 1, &pD3DSampler); break;
//	default:
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
////! Set Shader pipline
//DrBool DrDeviceContext::SetShader(DrShaderEffect* se)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//	//=========================================
//	//! シェーダのアクティブフラグを初期化
//	//=========================================
//	m_activeShaders[VS_IDX] =
//		m_activeShaders[PS_IDX] =
//		m_activeShaders[GS_IDX] =
//		m_activeShaders[HS_IDX] =
//		m_activeShaders[DS_IDX] =
//		m_activeShaders[CS_IDX] = DR_FALSE;
//
//	// ShaderEffectがnullならすべてのシェーダをnullにする
//	if (se == nullptr)
//	{
//		m_pDeviceContext->VSSetShader(nullptr, nullptr, 0);
//		m_pDeviceContext->PSSetShader(nullptr, nullptr, 0);
//		m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);
//		m_pDeviceContext->CSSetShader(nullptr, nullptr, 0);
//		m_pDeviceContext->HSSetShader(nullptr, nullptr, 0);
//		m_pDeviceContext->DSSetShader(nullptr, nullptr, 0);
//
//		DrDebugLog(" Shader Effect = null\n");
//		return DR_FALSE;
//	}
//	//=========================================
//	//! アクティブシェーダの更新
//	//=========================================
//	if (se->GetVertexShader() && se->GetVertexShader()->GetShader())
//		m_activeShaders[VS_IDX] = DR_TRUE;
//	if (se->GetPixelShader() && se->GetPixelShader()->GetShader())
//		m_activeShaders[PS_IDX] = DR_TRUE;
//	if (se->GetGeometryShader() && se->GetGeometryShader()->GetShader())
//		m_activeShaders[GS_IDX] = DR_TRUE;
//	if (se->GetHullShader() && se->GetHullShader()->GetShader())
//		m_activeShaders[HS_IDX] = DR_TRUE;
//	if (se->GetDomainShader() && se->GetDomainShader()->GetShader())
//		m_activeShaders[DS_IDX] = DR_TRUE;
//	if (se->GetComputeShader() && se->GetComputeShader()->GetShader())
//		m_activeShaders[CS_IDX] = DR_TRUE;
//
//	//=========================================
//	// ! アクティブシェーダをコンテキストに登録
//	//=========================================
//	if (m_activeShaders[VS_IDX])
//		m_pDeviceContext->VSSetShader(se->GetVertexShader()->GetShader(), nullptr, 0);
//	else
//		m_pDeviceContext->VSSetShader(nullptr, nullptr, 0);
//	if (m_activeShaders[PS_IDX])
//		m_pDeviceContext->PSSetShader(se->GetPixelShader()->GetShader(), nullptr, 0);
//	else
//		m_pDeviceContext->PSSetShader(nullptr, nullptr, 0);
//
//	if (m_activeShaders[GS_IDX])
//		m_pDeviceContext->GSSetShader(se->GetGeometryShader()->GetShader(), nullptr, 0);
//	else
//		m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);
//
//	if (m_activeShaders[HS_IDX])
//		m_pDeviceContext->HSSetShader(se->GetHullShader()->GetShader(), nullptr, 0);
//	else
//		m_pDeviceContext->HSSetShader(nullptr, nullptr, 0);
//
//	if (m_activeShaders[DS_IDX])
//		m_pDeviceContext->DSSetShader(se->GetDomainShader()->GetShader(), nullptr, 0);
//	else
//		m_pDeviceContext->DSSetShader(nullptr, nullptr, 0);
//
//	if (m_activeShaders[CS_IDX])
//		m_pDeviceContext->CSSetShader(se->GetComputeShader()->GetShader(), nullptr, 0);
//	else
//		m_pDeviceContext->CSSetShader(nullptr, nullptr, 0);
//
//	//=========================================
//	// VertexShader Or PixelShader 
//	// 設定されていないときはグラボがクラッシュする。
//	//=========================================
//	if ((m_activeShaders[VS_IDX] &&
//		m_activeShaders[PS_IDX]) == DR_FALSE)
//	{
//		DrDebugLogError("VertexShader OR PixelShader = null\n");
//		return DR_FALSE;
//	}
//	m_bindShaderEffect = se;
//	return DR_TRUE;
//}
//
////! レンダーターゲットを設定する。(この時点ではまだデバイスには反映されない。)
//DrBool DrDeviceContext::SetRT(DrInt index, DrRenderTarget* view)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	if ((unsigned)index > MAX_RDr)
//	{
//		DrDebugLogError("Out Of Range\n");
//		return DR_FALSE;
//	}
//	m_renderTarget[index] = view;
//
//	return DR_TRUE;
//}
//
////! RenderTargetの変更を適用する
//DrBool DrDeviceContext::ApplyRenderTargets()
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	ID3D11RenderTargetView * renderTargets[MAX_RDr];
//	ID3D11DepthStencilView * dsv = nullptr;
//
//	if (m_depthStencil != nullptr)
//	{
//		dsv = m_depthStencil->GetDSV();
//	}
//
//	int rtNum = 0;
//	for (; rtNum < MAX_RDr; ++rtNum)
//	{
//		if (m_renderTarget[rtNum] == nullptr)
//			break;
//		else
//			renderTargets[rtNum] = m_renderTarget[rtNum]->GetRTV();
//	}
//
//	if (rtNum == 0)
//	{
//		DrDebugLogError("RenderTargets = null\n");
//		return DR_FALSE;
//	}
//
//	m_pDeviceContext->OMSetRenderTargets(rtNum, renderTargets, dsv);
//
//	return DR_TRUE;
//}
//
////! 実際にスクリーンに反映されるレンダーターゲットを設定する
//DrBool DrDeviceContext::SetScreenRTV(DrRenderTarget * pRtv)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	m_mainRenderTarget = pRtv;
//	return DR_TRUE;
//}
//
//
////! Set Depth Stencil
//DrBool DrDeviceContext::SetDepthStencilView(DrDepthStencilView* dsv)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//	if (dsv)
//		m_depthStencil = dsv;
//	return DR_TRUE;
//}
//
////! Set Depth Stencil
//DrBool DrDeviceContext::SetMainDepthStencil(DrDepthStencilView* dsv)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	m_mainDepthStencil = dsv;
//	return DR_TRUE;
//}
//
//// ! Set & Change the CBuffer.
//DrBool DrDeviceContext::SetAndChangeCBuffer(DrCBuffer* cbuffer,
//	void * pData,
//	size_t size)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	DrBool hr;
//	hr = ChangeCBuffer(cbuffer, pData, size);
//	if (hr == DR_FALSE)return DR_FALSE;
//
//	hr = SetCBuffer(cbuffer);
//	if (hr == DR_FALSE) return DR_FALSE;
//
//	return DR_TRUE;
//}
//
////! Set CBuffer
//DrBool DrDeviceContext::SetCBuffer(const DrCBuffer * cbuffer)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	if (cbuffer == nullptr)
//		return DR_FALSE;
//
//	ID3D11Buffer* buffer = cbuffer->GetBuffer();
//
//	auto shaderType = cbuffer->GetBindShaderType();
//
//	if (buffer == nullptr)
//		return DR_FALSE;
//
//	if (DRShaderUT::IsVS(shaderType))
//		m_pDeviceContext->VSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
//	if (DRShaderUT::IsPS(shaderType))
//		m_pDeviceContext->PSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
//	if (DRShaderUT::IsGS(shaderType))
//		m_pDeviceContext->CSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
//	if (DRShaderUT::IsHS(shaderType))
//		m_pDeviceContext->HSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
//	if (DRShaderUT::IsCS(shaderType))
//		m_pDeviceContext->CSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
//	if (DRShaderUT::IsDS(shaderType))
//		m_pDeviceContext->DSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
//
//	if (shaderType == DR_SHADER_TYPE::UNKNOWN_SHADER)
//	{
//		DrDebugLogError("Set CBuffer Error.\n");
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
//void* DrDeviceContext::Map(DrBuffer* pBuffer, D3D11_MAP mapType)
//{
//	ID3D11Buffer* buffer = pBuffer->GetBuffer();
//
//	if (buffer == nullptr)
//		return DR_FALSE;
//
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//
//	HRESULT hr = m_pDeviceContext->Map(pBuffer->GetBuffer(), 0, mapType, 0, &mappedResource);
//	if (hr != S_OK)
//	{
//		DrDebugLogError("Gpuリソースへのアクセスに失敗\n");
//		return nullptr;
//	}
//
//	return mappedResource.pData;
//}
//
//DrBool DrDeviceContext::UnMap(DrBuffer* pBuffer)
//{
//	m_pDeviceContext->Unmap(pBuffer->GetBuffer(), 0);
//
//	return DR_TRUE;
//}
//
////! Change CBuffer
//DrBool DrDeviceContext::ChangeCBuffer(DrCBuffer * cbuffer, void * pData, size_t sz)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	if (cbuffer == nullptr)
//		return DR_FALSE;
//
//	ID3D11Buffer* buffer = cbuffer->GetBuffer();
//
//	if (buffer == nullptr)
//		return DR_FALSE;
//
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//
//	HRESULT hr = m_pDeviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
//	if (hr == S_OK)
//	{
//		CopyMemory(mappedResource.pData, pData, sz);
//
//		m_pDeviceContext->Unmap(buffer, 0);
//	}
//	else
//	{
//		DrDebugLogError("Gpuリソースへの書き込みに失敗\n");
//		return DR_FALSE;
//	}
//
//	return DR_TRUE;
//}
//
////! Draw Call
//DrBool DrDeviceContext::Draw(DrInt vtxNum, DrInt startSlot)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	DrBool isActiveVSandPS = m_activeShaders[VS_IDX] & m_activeShaders[PS_IDX];
//
//	if (isActiveVSandPS)
//	{
//		m_pDeviceContext->Draw(vtxNum, startSlot);
//		m_drawCallCount++;
//	}
//	else
//	{
//		DrDebugLogError("Fail Draw Call Vertex Or PixelShader Is Null\n");
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::DrawIndex(DrInt index, DrInt startSlot, DrInt indexLocation)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	DrBool isActiveVSandPS = m_activeShaders[VS_IDX] & m_activeShaders[PS_IDX];
//
//	if (isActiveVSandPS)
//	{
//		m_pDeviceContext->DrawIndexed(index, startSlot, indexLocation);
//		m_drawCallCount++;
//	}
//	else
//	{
//		DrDebugLogError("Fail Draw Call Vertex Or PixelShader Is Null\n");
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::DrawInstance(DrInt vertexNum,
//	DrInt instanceNum,
//	DrInt instanceLocation,
//	DrInt startSlot)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	DrBool isActiveVSandPS = m_activeShaders[VS_IDX] & m_activeShaders[PS_IDX];
//
//	if (isActiveVSandPS)
//	{
//		m_pDeviceContext->DrawInstanced(vertexNum, instanceNum, startSlot, instanceLocation);
//		m_drawCallCount++;
//	}
//	else
//	{
//		DrDebugLogError("Fail Draw Call Vertex Or PixelShader Is Null\n");
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::DrawIndexInstance(DrInt index,
//	DrInt instanceNum,
//	DrInt instanceLocation,
//	DrInt startSlot,
//	DrInt indexLocation)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	DrBool isActiveVSandPS = m_activeShaders[VS_IDX] & m_activeShaders[PS_IDX];
//
//	if (isActiveVSandPS)
//	{
//		m_pDeviceContext->DrawIndexedInstanced(index, instanceNum, startSlot, indexLocation, instanceLocation);
//		m_drawCallCount++;
//	}
//	else
//	{
//		DrDebugLogError("Fail Draw Call Vertex Or PixelShader Is Null\n");
//		return DR_FALSE;
//	}
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::ResetDrawCallCount()
//{
//	m_drawCallCount = 0;
//	return DR_TRUE;
//}
//
////! Set View port
//DrBool DrDeviceContext::SetViewport(DrViewport* viewport)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	if (viewport == nullptr)
//		return DR_FALSE;
//	m_pDeviceContext->RSSetViewports(1, viewport->GetD3DViewport());
//
//	return DR_TRUE;
//}
//
////! Apply Inputlayout
//DrBool DrDeviceContext::ApplyInputLayout()
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	if (m_activeShaders[VS_IDX] == DR_FALSE)
//		return DR_FALSE;
//
//	if (m_bindShaderEffect == nullptr)
//		return DR_FALSE;
//
//	auto inputLayout = m_bindShaderEffect->GetInputLayout();
//	m_pDeviceContext->IASetInputLayout(inputLayout);
//
//	return DR_TRUE;
//}
//
////! SetVertexBuffer
//DrBool DrDeviceContext::SetVertexBuffer(DrVertexBuffer* vb)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	if (vb == nullptr)
//	{
//		DRUT::DrLog("VertexBuffer is null\n");
//		return DR_FALSE;
//	}
//
//	ID3D11Buffer* buffer = vb->GetBuffer();
//	DrUint size = vb->GetBufferSize();
//	DrUint stride = vb->GetStride();
//	DrUint offset = vb->GetOffset();
//	if (buffer == nullptr || size == 0 || stride == 0)
//	{
//		DRUT::DrLog("VertexBuffer is null\n");
//		return DR_FALSE;
//	}
//
//	m_pDeviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
//
//	return DR_TRUE;
//}
//
////! SetIndexBuffer
//DrBool DrDeviceContext::SetIndexBuffer(DrIndexBuffer* pBuffer)
//{
//	m_pDeviceContext->IASetIndexBuffer(pBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::SetRasterizerState(DrRasterizerState* raster)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	m_pRasterizerState = raster;
//
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::SetBlendState(DrBlendState* pBlendState)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	m_pBlendState = pBlendState;
//
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::SetDepthStencilState(DrDepthStencilState*  pDepthStencil)
//{
//	if (m_pDeviceContext == nullptr)
//		return DR_FALSE;
//
//	m_pDepthStencilState = pDepthStencil;
//	return DR_TRUE;
//}
//
//DrCamera * DrDeviceContext::GetMainCamera()const
//{
//	//todo test
//	if (m_mainCamera == nullptr)
//	{
//		static DrCamera defaultCamera;
//		return &defaultCamera;
//	}
//	return m_mainCamera;
//}
//
//DrBool DrDeviceContext::SetMainCamera(DrCamera* camera)
//{
//	m_mainCamera = camera;
//	return DR_TRUE;
//}
//DrBool DrDeviceContext::SetTopology(D3D_PRIMITIVE_TOPOLOGY topology)
//{
//	m_pDeviceContext->IASetPrimitiveTopology(topology);
//	return DR_TRUE;
//}
//
//
//DrBool DrDeviceContext::ApplyDepthStencil()
//{
//	if (m_pDeviceContext)
//		m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState->GetDSS(), 0);
//	return DR_TRUE;
//}
//DrBool DrDeviceContext::ApplyRasterizer()
//{
//	if (m_pDeviceContext)
//		m_pDeviceContext->RSSetState(m_pRasterizerState->GetRSS());
//	return DR_TRUE;
//}
//DrBool DrDeviceContext::ApplyBlendState()
//{
//	if (m_pDeviceContext)
//	{
//		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
//		m_pDeviceContext->OMSetBlendState(m_pBlendState->GetBlendState(), blendFactor, 0xffffff);
//	}
//	return DR_TRUE;
//}
//
//DrBool DrDeviceContext::ClearVertexBuffer()
//{
//	return DR_FALSE;
//}
//DrBool DrDeviceContext::ClearIndexBuffer()
//{
//	return DR_FALSE;
//}
//DrBool DrDeviceContext::ClearCBuffer(DrInt index, DR_SHADER_TYPE type)
//{
//	DrInt count = 1;
//	if (index < 0)
//	{
//		index = 0;
//		count = 16;
//	}
//	if (index > 15)
//	{
//		return DR_FALSE;
//	}
//
//	if (type & DR_SHADER_TYPE::VERTEX_SHADER & type)
//		m_pDeviceContext->VSSetConstantBuffers(index, count, nullptr);
//	if (type & DR_SHADER_TYPE::PIXEL_SHADER & type)
//		m_pDeviceContext->PSSetConstantBuffers(index, count, nullptr);
//	if (type & DR_SHADER_TYPE::GEOMETRY_SHADER & type)
//		m_pDeviceContext->GSSetConstantBuffers(index, count, nullptr);
//	if (type & DR_SHADER_TYPE::HULL_SHADER & type)
//		m_pDeviceContext->HSSetConstantBuffers(index, count, nullptr);
//	if (type & DR_SHADER_TYPE::DOMAIN_SHADER & type)
//		m_pDeviceContext->DSSetConstantBuffers(index, count, nullptr);
//	if (type & DR_SHADER_TYPE::COMPUTE_SHADER & type)
//		m_pDeviceContext->CSSetConstantBuffers(index, count, nullptr);
//
//	return DR_TRUE;
//}
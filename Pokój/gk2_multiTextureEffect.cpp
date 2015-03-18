#include "gk2_multiTextureEffect.h"

using namespace std;
using namespace gk2;


const wstring MultiTextureEffect::ShaderFile = L"resources/shaders/MultiTextureShader.hlsl";

MultiTextureEffect::MultiTextureEffect(DeviceHelper& device, shared_ptr<ID3D11InputLayout>& layout,
						 shared_ptr<ID3D11DeviceContext> context /* = nullptr */)
	: EffectBase(context)
{
	Initialize(device, layout, ShaderFile);
}

void MultiTextureEffect::SetTextureMtxBuffers(const std::shared_ptr<gk2::CBMatrix>& textureMtx1, const std::shared_ptr<gk2::CBMatrix>& textureMtx2)
{
	if (textureMtx1 != nullptr)
		m_textureMtxCB1 = textureMtx1;
	if (textureMtx2 != nullptr)
		m_textureMtxCB2 = textureMtx2;
}

void MultiTextureEffect::SetSamplerState(const shared_ptr<ID3D11SamplerState>& samplerState)
{
	if (samplerState != nullptr)
		m_samplerState = samplerState;
}

void MultiTextureEffect::SetTextures(const std::shared_ptr<ID3D11ShaderResourceView>& texture1, const std::shared_ptr<ID3D11ShaderResourceView>& texture2)
{
	if (texture1 != nullptr)
		m_texture1 = texture1;
	if (texture2 != nullptr)
		m_texture2 = texture2;
}


void MultiTextureEffect::SetVertexShaderData()
{
	//These are b0 - b4 parameters in the MultiTextureShader
	ID3D11Buffer* vsb[5] = { m_worldCB->getBufferObject().get(), m_viewCB->getBufferObject().get(),
							 m_projCB->getBufferObject().get(), m_textureMtxCB1->getBufferObject().get(),
							 m_textureMtxCB2->getBufferObject().get()};
	m_context->VSSetConstantBuffers(0, 5, vsb);
}

void MultiTextureEffect::SetPixelShaderData()
{
	ID3D11SamplerState* ss[1] = { m_samplerState.get() };
	m_context->PSSetSamplers(0, 1, ss);
	//These are t0 - t1 parameters in the MultiTextureShader
	ID3D11ShaderResourceView* srv[2] = { m_texture1.get(), m_texture2.get() };
	m_context->PSSetShaderResources(0, 2, srv);
}
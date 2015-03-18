#ifndef __GK2_MULTI_TEXTURE_EFFECT_H_
#define __GK2_MULTI_TEXTURE_EFFECT_H_

#include "gk2_effectBase.h"

namespace gk2
{
	class MultiTextureEffect : public EffectBase
	{
	public:
		MultiTextureEffect(gk2::DeviceHelper& device, std::shared_ptr<ID3D11InputLayout>& layout,
					  std::shared_ptr<ID3D11DeviceContext> context = nullptr);

		void SetTextureMtxBuffers(const std::shared_ptr<gk2::CBMatrix>& textureMtx1, const std::shared_ptr<gk2::CBMatrix>& textureMtx2);
		void SetSamplerState(const std::shared_ptr<ID3D11SamplerState>& samplerState);
		void SetTextures(const std::shared_ptr<ID3D11ShaderResourceView>& texture1, const std::shared_ptr<ID3D11ShaderResourceView>& texture2);

	protected:
		virtual void SetVertexShaderData();
		virtual void SetPixelShaderData();

	private:
		static const std::wstring ShaderFile;
		
		std::shared_ptr<gk2::CBMatrix> m_textureMtxCB1;
		std::shared_ptr<gk2::CBMatrix> m_textureMtxCB2;
		std::shared_ptr<ID3D11SamplerState> m_samplerState;
		std::shared_ptr<ID3D11ShaderResourceView> m_texture1;
		std::shared_ptr<ID3D11ShaderResourceView> m_texture2;
	};
}

#endif __GK2_MULTI_TEXTURE_EFFECT_H_

#pragma once
#include "IDRGenerator.h"

namespace Graphics
{
	class IRenderInterface
	{
	public:
		IRenderInterface(RefCounterPtr<IConstBuffer>& _ConstBuffer)
			: ConstBuffer(_ConstBuffer)
			, BeRender(true)
		{
		}
		virtual ~IRenderInterface()
		{
		}

	public:

		virtual void BindResourceToPipeline(UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const = 0;

		void UpdateConstBuffer() const
		{
			ConstBuffer->UpdateBuffer();
		}
		void SetRender(bool _BeRender) { BeRender = _BeRender; }
		bool IsRender() const { return BeRender; }

	protected:
		RefCounterPtr<IConstBuffer> ConstBuffer;

		bool BeRender;

	};

	class SpriteInterface : public IRenderInterface
	{
		using Super = IRenderInterface;
	public:
		SpriteInterface(RefCounterPtr<IConstBuffer>& _ConstBuffer, RefCounterPtr<IShaderResource>& _Image)
			: Super(_ConstBuffer)
			, Image(_Image)
		{
		}
		~SpriteInterface() {}

	public:
		void BindResourceToPipeline(UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const override
		{
			if (!BeRender)
				return;

			ConstBuffer->VSSetConstBuffers(_ConstBufferStartSlot);
			ConstBuffer->PSSetConstBuffers(_ConstBufferStartSlot);
			Image->VSSetShaderResources(_ShaderResourceStartSlot);
			Image->PSSetShaderResources(_ShaderResourceStartSlot);
		}

	private:
		RefCounterPtr<IShaderResource> Image;

	};
}
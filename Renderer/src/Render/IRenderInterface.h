#pragma once
#include "IDRGenerator.h"
#include "GraphicsTime.h"
#include "Base/Notify.h"

namespace Graphics
{
	class RENDERER_API IRenderInterface
	{
	public:
		IRenderInterface(RefCounterPtr<IConstBuffer>& _ConstBuffer)
			: ConstBuffer(_ConstBuffer)
			, BeRender(true)
		{
		}
		IRenderInterface()
			: ConstBuffer(nullptr)
			, BeRender(true)
		{
		}
		~IRenderInterface()
		{
		}

	public:
		void BindResourceToPipeline(UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const
		{
			if (!BeRender)
				return;

			ConstBuffer->VSSetConstBuffers(_ConstBufferStartSlot);
			ConstBuffer->PSSetConstBuffers(_ConstBufferStartSlot);

			Image->VSSetShaderResources(_ShaderResourceStartSlot);
			Image->PSSetShaderResources(_ShaderResourceStartSlot);
			
		}

		void UpdateConstBuffer() const
		{
			ConstBuffer->UpdateBuffer();
		}

		void SetConstBuffer(RefCounterPtr<IConstBuffer>& _ConstBuffer)
		{
			ConstBuffer = _ConstBuffer;
		}

		Vector2 GetImageSize(size_t _Index)
		{
			return Image->GetImageSize(_Index);
		}

		void SetImage(RefCounterPtr<IShaderResource>& _Image) { Image = _Image; }

		void SetRender(bool _BeRender) { BeRender = _BeRender; }
		bool IsRender() const { return BeRender; }

	protected:
		RefCounterPtr<IConstBuffer> ConstBuffer;
		RefCounterPtr<IShaderResource> Image;

		bool BeRender;
	};

}
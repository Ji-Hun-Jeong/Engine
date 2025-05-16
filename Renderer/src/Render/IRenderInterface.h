#pragma once
#include "IDRGenerator.h"

#include <Engine/src/Time/Time.h>

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

	class RENDERER_API SpriteInterface : public IRenderInterface
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

	class RENDERER_API Animation
	{
	public:
		Animation(float _FrameTime)
			: FrameTime(_FrameTime)
			, ProgressTime(0.0f)
			, CurrentFrame(0)
		{}
		~Animation() {}

	public:
		void ExitAnimation()
		{
			ProgressTime = 0.0f;
			CurrentFrame = 0;
		}

		void Update(UINT _StartSlot);

		void AddImage(RefCounterPtr<IShaderResource>& Image)
		{
			Images.push_back(Image);
		}

	private:
		std::vector<RefCounterPtr<IShaderResource>> Images;

		float FrameTime;
		float ProgressTime;

		UINT CurrentFrame;

	};

	class RENDERER_API AnimationTransition
	{
	public:
		AnimationTransition(Animation* _Tail, Animation* _Head, std::function<bool()> _Condition)
			: Tail(_Tail), Head(_Head), Condition(_Condition)
		{}
		~AnimationTransition() = default;

	public:


	private:
		Animation* Tail;
		Animation* Head;

		std::function<bool()> Condition;
	};

	class RENDERER_API AnimationInterface : public IRenderInterface
	{
		using Super = IRenderInterface;
	public:
		AnimationInterface(RefCounterPtr<IConstBuffer>& _ConstBuffer)
			: Super(_ConstBuffer)
			, CurrentAnimation(nullptr)
		{
		}
		~AnimationInterface() 
		{
			for (auto& Animation : Animations)
				delete Animation.second;
		}
		
	public:
		void BindResourceToPipeline(UINT _ConstBufferStartSlot, UINT _ShaderResourceStartSlot) const override
		{
			if (!BeRender)
				return;

			ConstBuffer->VSSetConstBuffers(_ConstBufferStartSlot);
			ConstBuffer->PSSetConstBuffers(_ConstBufferStartSlot);

			CurrentAnimation->Update(_ShaderResourceStartSlot);
		}

		void AddAnimation(const Str::FString& _AnimationName, Animation* _Animation)
		{
			Animations.insert(std::make_pair(_AnimationName, _Animation));
		}

		void SetCurrentAnimation(const Str::FString& _AnimationName)
		{
			if (CurrentAnimation)
				CurrentAnimation->ExitAnimation();
			
			CurrentAnimation = Animations.find(_AnimationName)->second;
		}

	private:
		std::map<Str::FString, Animation*> Animations;
		Animation* CurrentAnimation;

	};
}
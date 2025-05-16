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

	class RENDERER_API SpriteRenderer : public IRenderInterface
	{
		using Super = IRenderInterface;
	public:
		SpriteRenderer(RefCounterPtr<IConstBuffer>& _ConstBuffer, RefCounterPtr<IShaderResource>& _Image)
			: Super(_ConstBuffer)
			, Image(_Image)
		{
		}
		~SpriteRenderer() {}

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

	class RENDERER_API Animation : public IEventNotifier
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

		bool IsFinish;
	};

	class RENDERER_API AnimationTransition : public IEventListener
	{
	public:
		AnimationTransition(Animation* _Tail, Animation* _Head, std::function<bool()> _Condition, std::function<void(Animation*)> _ChangeAnimationFunc)
			: Tail(_Tail), Head(_Head)
			, Condition(_Condition)
			, ChangeAnimationFunc(_ChangeAnimationFunc)
			, ForceExit(false)
		{}
		~AnimationTransition() = default;

	public:
		void DispatchEvent() override
		{
			if(ForceExit == false)
				Tail->
			if (Condition())
				ChangeAnimationFunc(Head);
		}

	private:
		Animation* Tail;
		Animation* Head;

		std::function<bool()> Condition;
		std::function<void(Animation*)> ChangeAnimationFunc;

		bool ForceExit;
	};

	class RENDERER_API Animator : public IRenderInterface
	{
		using Super = IRenderInterface;
	public:
		Animator(RefCounterPtr<IConstBuffer>& _ConstBuffer)
			: Super(_ConstBuffer)
			, CurrentAnimation(nullptr)
		{
		}
		~Animator() 
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

		void SetCurrentAnimation(Animation* _Animation)
		{
			if (CurrentAnimation)
				CurrentAnimation->ExitAnimation();

			CurrentAnimation = _Animation;
		}

	private:
		std::map<Str::FString, Animation*> Animations;
		Animation* CurrentAnimation;

	};
}
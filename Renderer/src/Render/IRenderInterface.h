#pragma once
#include "IDRGenerator.h"
#include "GraphicsTime.h"
#include "Base/Notify.h"

namespace Graphics
{
	/*class RENDERER_API IRenderInterface
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

	};*/

	class RENDERER_API RenderInterface
	{
	public:
		RenderInterface(RefCounterPtr<IConstBuffer>& _ConstBuffer)
			: ConstBuffer(_ConstBuffer)
			, BeRender(true)
		{
		}
		~RenderInterface()
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

		void SetImage(RefCounterPtr<IShaderResource>& _Image) { Image = _Image; }

		void SetRender(bool _BeRender) { BeRender = _BeRender; }
		bool IsRender() const { return BeRender; }

	protected:
		RefCounterPtr<IConstBuffer> ConstBuffer;
		RefCounterPtr<IShaderResource> Image;

		bool BeRender;
	};

	/*class RENDERER_API SpriteRenderer : public IRenderInterface
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
		Animation(float _FrameTime, bool _Repeat)
			: FrameTime(_FrameTime)
			, ProgressTime(FrameTime)
			, CurrentFrame(-1)
			, Repeat(_Repeat)
			, Finish(false)
		{}
		~Animation() {}

	public:
		struct FrameInfo
		{
			RefCounterPtr<IShaderResource> FrameImage;
			std::function<void()> FrameEvent;
		};

		void ResetAnimation()
		{
			ProgressTime = FrameTime;
			CurrentFrame = -1;
		}

		void Update(UINT _StartSlot);

		void AddFrameInfo(RefCounterPtr<IShaderResource>& _Image, std::function<void()> _FrameEvent = nullptr)
		{
			FrameInfos.push_back({ _Image, _FrameEvent });
		}

		bool IsFinish() const { return Finish; }

		bool IsRepeat() const { return Repeat; }

	private:
		std::vector<FrameInfo> FrameInfos;

		float FrameTime;
		float ProgressTime;

		UINT CurrentFrame;

		bool Repeat;
		bool Finish;
	};

	class RENDERER_API AnimationTransition : public IEventListener
	{
	public:
		AnimationTransition(Animation* _Tail, Animation* _Head, std::function<bool()> _Condition, std::function<void(Animation*)> _ChangeAnimationFunc)
			: Tail(_Tail), Head(_Head), SatisfyCondition(false)
			, Condition(_Condition)
			, ChangeAnimationFunc(_ChangeAnimationFunc)
			, ForceExit(false)
			, Timer(2.0f)
		{
			
		}
		~AnimationTransition()
		{
			
		}

	public:
		void ExecuteEvent() override
		{
			Timer.GoOn();

			if (Condition())
			{
				SatisfyCondition = true;
				Timer.SetRun(true);
			}

			if (Timer.IsTimeOver())
			{
				SatisfyCondition = false;
				Timer.Reset();
				Timer.SetRun(false);
			}

			if (ForceExit == false && Tail->IsFinish() == false)
				return;

			if (SatisfyCondition)
				ChangeAnimationFunc(Head);

			SatisfyCondition = false;
		}

		void SetForceExit(bool _ForceExit) { ForceExit = _ForceExit; }

	private:
		Animation* Tail;
		Animation* Head;

		bool SatisfyCondition;

		GraphicsTime::Timer Timer;

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
				CurrentAnimation->ResetAnimation();
			
			CurrentAnimation = Animations.find(_AnimationName)->second;
		}

		void SetCurrentAnimation(Animation* _Animation)
		{
			if (CurrentAnimation)
				CurrentAnimation->ResetAnimation();

			CurrentAnimation = _Animation;
		}

		Animation* FindAnimation(const Str::FString& _AnimationName)
		{
			auto Iter = Animations.find(_AnimationName);
			if (Iter == Animations.end())
				return nullptr;
			return Iter->second;
		}

	private:
		std::map<Str::FString, Animation*> Animations;
		Animation* CurrentAnimation;

	};*/

}
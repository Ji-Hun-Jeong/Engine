#pragma once
#include "Object/Object.h"

#include <Renderer/src/Interface/IConstBuffer.h>

namespace Game
{
	class Camera : public Object
	{
		using Super = Object;
		CLONE(Camera, Object)
	public:
		Camera(const Str::FString& _Name)
			: Super(_Name)
		{}
		~Camera() {}

	public:
		virtual void Update() override
		{
			Super::Update();
			ViewProj = Transform.GetModel().Invert().Transpose();
			ConstBuffer->UpdateBuffer();
		}

		const Matrix& GetViewProj() const { return ViewProj; }

		RefCounterPtr<Graphics::IConstBuffer> InitalizeGlobalConst(Graphics::IDRGenerator& _Generator)
		{
			Graphics::CpuConstData ConstData{ &ViewProj, sizeof(ViewProj) };
			ConstBuffer = _Generator.GenerateConstBuffer({ ConstData });
			return ConstBuffer;
		}
	private:
		Matrix ViewProj;
		RefCounterPtr<Graphics::IConstBuffer> ConstBuffer;

	};
}

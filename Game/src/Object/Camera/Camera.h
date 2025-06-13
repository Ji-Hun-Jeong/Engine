#pragma once
#include "Object/Object.h"

#include <Renderer/src/Interface/IConstBuffer.h>

namespace Game
{
	struct CameraConst
	{
		Matrix ViewProj;
		Matrix InvViewProj;
		UINT ScreenWidth;
		UINT ScreenHeight;
		Vector2 Dummy1;
	};

	class Camera : public Object
	{
		using Super = Object;
		CLONE(Camera, Object)
	public:
		Camera(const Str::FString& _Name, UINT _ScreenWidth, UINT _ScreenHeight)
			: Super(_Name)
		{
			CameraConst.ScreenWidth = _ScreenWidth;
			CameraConst.ScreenHeight = _ScreenHeight;
		}
		~Camera() {}

	public:
		virtual void Update() override
		{
			Super::Update();
			CameraConst.InvViewProj = Transform.GetModel().Transpose();
			CameraConst.ViewProj = Transform.GetModel().Invert().Transpose();
			ConstBuffer->UpdateBuffer();
		}

		const Matrix& GetViewProj() const { return CameraConst.ViewProj; }

		RefCounterPtr<Graphics::IConstBuffer> InitalizeGlobalConst(Graphics::IDRGenerator& _Generator)
		{
			Graphics::CpuConstData ConstData{ &CameraConst, sizeof(CameraConst) };
			ConstBuffer = _Generator.GenerateConstBuffer({ ConstData });
			return ConstBuffer;
		}

	private:
		CameraConst CameraConst;
		RefCounterPtr<Graphics::IConstBuffer> ConstBuffer;

	};
}

#pragma once
#include "Object/Actor.h"

namespace Game
{
	class Camera : public Actor
	{
		using Super = Actor;
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
		}

		const Matrix& GetViewProj() const { return ViewProj; }

	private:
		Matrix ViewProj;

	};
}

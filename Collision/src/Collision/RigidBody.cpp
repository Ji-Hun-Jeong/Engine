#include "pch.h"
#include "RigidBody.h"

namespace Collision
{
	void RigidBody::Update(float _DT)
	{
		Force.y -= Gravity * Mass;

		Accel = Force / Mass;	// 가속도

		Velocity += Accel * _DT;

		// 반작용
		Vector2 NormVelocity = Velocity;
		NormVelocity.Normalize();
		if (0 < Velocity.Length())
			Velocity += -NormVelocity * Coeff * _DT;

		const float AbsVelocityX = std::abs(Velocity.x);
		const float AbsVelocityY = std::abs(Velocity.y);
		if (AbsVelocityX < 1.0f)
			Velocity.x = 0.0f;

		if (AbsVelocityY < 0.01f)
			Velocity.y = 0.0f;

		if (MaxSpeed < AbsVelocityX)
			Velocity.x = Velocity.x < 0 ? -MaxSpeed : MaxSpeed;
		if (MaxSpeed < AbsVelocityY)
			Velocity.y = Velocity.y < 0 ? -MaxSpeed : MaxSpeed;

		RefPosition += Vector3(Velocity.x, Velocity.y, 0.0f) * _DT;
		
		Force = Vector2();
	}
}
#pragma once

namespace Collision
{
	class COLLISION_API RigidBody
	{
	public:
		RigidBody(Vector3& _RefPosition)
			: RefPosition(_RefPosition)
			, MaxSpeed(0.7f)
			, Mass(0.1f)
			, Gravity(0.98f)
		{}
		~RigidBody() {}

	public:
		void Update(float _DT);

		void SetForce(const Vector2& _Force) { Force = _Force; }
		void SetAccel(const Vector2& _Accel) { Accel = _Accel; }
		void SetVelocity(const Vector2& _Velocity) { Velocity = _Velocity; }
		void SetCoeff(const Vector2& _Coeff) { Coeff = _Coeff; }
		void SetMass(float _Mass) { Mass = _Mass; }

		void AddForce(const Vector2& _Force) { Force += _Force; }
		void AddtAccel(const Vector2& _Accel) { Accel += _Accel; }
		void AddVelocity(const Vector2& _Velocity) { Velocity += _Velocity; }
		void AddCoeff(const Vector2& _Coeff) { Coeff += _Coeff; }
		void AddMass(float _Mass) { Mass += _Mass; }

		const Vector2& GetForce() const { return Force; }
		const Vector2& GetAccel() const { return Accel; }
		const Vector2& GetVelocity() const { return Velocity; }
		const Vector2& GetCoeff() const { return Coeff; }
		float		   GetMass() const { return Mass; }

	private:
		Vector2 Force;
		Vector2 Accel;
		Vector2 Velocity;
		Vector2 Coeff;

		float MaxSpeed;
		float Mass;
		float Gravity;

		Vector3& RefPosition;

	};
}



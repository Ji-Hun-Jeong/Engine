#pragma once
#include <Engine/src/Time/Time.h>

namespace Game
{
	class Transform
	{
	public:
		Transform() 
			: Transform(Vector3(0.0f))
		{}
		Transform(const Vector3& _Position)
			: Position(_Position)
			, Rotation(Vector3(0.0f))
			, Scale(Vector3(1.0f))
		{}
		~Transform() {}

	public:
		Matrix GetModel() const 
		{
			return Matrix::CreateScale(Scale)
				* Matrix::CreateRotationX(Rotation.x)
				* Matrix::CreateRotationY(Rotation.y)
				* Matrix::CreateRotationZ(Rotation.z)
				* Matrix::CreateTranslation(Position);
		}
		void SetScale(const Vector3& _Scale) { Scale = _Scale; }
		const Vector3& GetScale() const { return Scale; }
		void SetRotation(const Vector3& _Rotation) { Rotation = _Rotation; }
		const Vector3& GetRotation() const { return Rotation; }
		void SetPosition(const Vector3& _Position) { Position = _Position; }
		const Vector3& GetPosition() const { return Position; }

		int GetDirection() const { return Direction; }
		void Move(float _Speed)
		{
			Position.x += _Speed * Time::GetDT();
			ChangeDirection(_Speed);
		}
		void ChangeDirection(float _Dir)
		{
			Direction = _Dir < 0 ? -1.0f : 1.0f;
		}

	private:
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;

		int Direction;
	};
}



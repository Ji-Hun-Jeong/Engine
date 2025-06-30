#pragma once
#include <Engine/src/Time/Time.h>

namespace Game
{
	class Transform
	{
	public:
		Transform()
			: Transform(Vector3(0.0f))
		{
		}
		Transform(const Vector3& _Position)
			: Position(_Position)
			, Rotation(Vector3(0.0f))
			, Scale(Vector3(1.0f))
			, Direction(-1.0f)
			, CanMove(true)
		{
		}
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
		Vector3& GetPositionRef() { return Position; }

		int GetDirection() const { return Direction; }
		void Move(const Vector3& _Axis, float _Speed)
		{
			if (CanMove == false)
				return;
			Position += _Axis * _Speed * Time::GetDT();
			ChangeDirection(_Axis.x);
		}
		void ChangeDirection(float _Dir)
		{
			Direction = _Dir < 0 ? -1.0f : 1.0f;
		}
		void SetMove(bool _CanMove)
		{
			CanMove = _CanMove;
		}

	private:
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;

		int Direction;
		bool CanMove;
	};
}



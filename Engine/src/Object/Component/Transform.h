#pragma once

namespace Engine
{
	class Transform
	{
	public:
		Transform() {}
		~Transform() {}

	public:
		void SetPos(const Vector2& _Position) { Position = _Position; }
		const Vector2& GetPos() const { return Position; }
		void SetSize(const Vector2& _Size) { Size = _Size; }
		const Vector2& GetSize() const { return Size; }

	private:
		Vector2 Position;
		Vector2 Size;
	};
}
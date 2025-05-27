#pragma once

namespace Collision
{
	class COLLISION_API Collider
	{
	public:
		Collider() = default;
		virtual ~Collider() = 0 {}

	public:
		void SetColliderType(uint8_t _ColliderType) { ColliderType = _ColliderType; }

		uint32_t GetColliderId() const { return ColliderId; }
		uint8_t GetColliderType() const { return ColliderType; }

	protected:
		// Collider에게 타입을 줘서 그 타입에 맞게 
		uint32_t ColliderId;
		uint8_t ColliderType;

	};

	class COLLISION_API CircleCollider : public Collider
	{
	public:
		CircleCollider()
			: Position(Vector2(0.0f))
			, Radius(1.0f)
		{}
		~CircleCollider() {}

	public:


	public:
		Vector2 Position;
		float Radius;
	};

	class COLLISION_API RectCollider : public Collider
	{
	public:
		RectCollider()
			: Position(Vector2(0.0f))
			, Size(Vector2(1.0f))
		{}
		~RectCollider() {}

	public:
		void f(CircleCollider* c)
		{

		}

	public:
		Vector2 Position;
		Vector2 Size;
	};
}


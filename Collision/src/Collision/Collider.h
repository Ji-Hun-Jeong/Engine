#pragma once

namespace Collision
{
	class COLLISION_API Collider
	{
	public:
		Collider()
			: ColliderId(-1)
			, ColliderType(-1)
			, Position(Vector3(0.0f))
			, Offset(Vector3(0.0f))
		{}
		virtual ~Collider() = 0;

	public:
		void AddCollisionEnter(std::function<void(Collider*)> _CollisionEnter) { CollisionEnterFuncs.push_back(_CollisionEnter); }
		void AddCollisionStay(std::function<void(Collider*)> _CollisionStay) { CollisionStayFuncs.push_back(_CollisionStay); }
		void AddCollisionExit(std::function<void(Collider*)> _CollisionExit) { CollisionExitFuncs.push_back(_CollisionExit); }

		void SetPosition(const Vector3& _Position) { Position = _Position + Offset; }
		void SetOffset(const Vector3& _Offset) { Offset = _Offset; }
		void SetColliderId(uint32_t _ColliderId) { ColliderId = _ColliderId; }
		void SetColliderType(uint8_t _ColliderType) { ColliderType = _ColliderType; }

		const Vector3& GetPosition() const { return Position; }
		uint32_t GetColliderId() const { return ColliderId; }
		uint8_t GetColliderType() const { return ColliderType; }

	public:
		void OnCollisionEnter(Collider* _Other)
		{
			for (auto& CollisionEnterFunc : CollisionEnterFuncs)
				CollisionEnterFunc(_Other);
		}
		void OnCollisionStay(Collider* _Other)
		{
			for (auto& CollisionStayFunc : CollisionStayFuncs)
				CollisionStayFunc(_Other);
		}
		void OnCollisionExit(Collider* _Other)
		{
			for (auto& CollisionExitFunc : CollisionExitFuncs)
				CollisionExitFunc(_Other);
		}


	protected:
		// Collider에게 타입을 줘서 그 타입에 맞게
		uint32_t ColliderId;
		uint8_t ColliderType;

		Vector3 Position;
		Vector3 Offset;

		std::vector<std::function<void(Collider*)>> CollisionEnterFuncs;
		std::vector<std::function<void(Collider*)>> CollisionStayFuncs;
		std::vector<std::function<void(Collider*)>> CollisionExitFuncs;
	};

	class COLLISION_API RectCollider : public Collider
	{
		using Super = Collider;
	public:
		RectCollider()
			: Super()
			, Size(Vector3(1.0f))
		{}
		~RectCollider() {}

	public:
		void SetSize(const Vector3& _Size) { Size = _Size; }
		const Vector3& GetSize() const { return Size; }

	public:
		Vector3 Size;
	};

	class COLLISION_API CircleCollider : public Collider
	{
		using Super = Collider;
	public:
		CircleCollider()
			: Super()
			, Radius(1.0f)
		{}
		~CircleCollider() {}

	public:


	public:
		float Radius;
	};

	

	extern bool COLLISION_API IsCollision(RectCollider* _Collider1, RectCollider* _Collider2);
	extern bool COLLISION_API IsCollision(RectCollider* _Collider1, CircleCollider* _Collider2);
	extern bool COLLISION_API IsCollision(CircleCollider* _Collider1, CircleCollider* _Collider2);
}


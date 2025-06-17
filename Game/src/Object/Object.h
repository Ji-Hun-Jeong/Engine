#pragma once
#include <Collision/src/Collision/CollisionDetector.h>
#include <Collision/src/Collision/RigidBody.h>

#include "Component/Transform/Transform.h"

namespace Game
{
	class Object
	{
	public:
		Object(const Str::FString& _Name);
		Object(const Object& _Other);
		Object(Object&& _Other) = delete;
		Object& operator = (const Object& _Other) = delete;
		Object& operator = (Object&& _Other) = delete;
		virtual ~Object();

	public:
		virtual Object* GetClone() const = 0;
		virtual void InitObject();
		virtual void Update();
		virtual void PostUpdate();
		virtual void Destory();

		virtual void InitalizeCollision(Collision::ColliderManager& _CollisionMgr) {}

		void SetName(const Str::FString& _Name) { Name = _Name; }
		const Str::FString& GetName() const { return Name; }

		void SetRigidBody(Collision::RigidBody* _RigidBody) { RigidBody = _RigidBody; }
		void Move(const Vector3& _Axis, float _Speed)
		{
			Transform.Move(_Axis, _Speed);
		}

		Collision::RigidBody& GetRigidBody() { return *RigidBody; }
		Vector3& GetPositionRef() { return Transform.GetPositionRef(); }
		const Vector3& GetPosition() const { return Transform.GetPosition(); }
		const Vector3& GetRotation() const { return Transform.GetRotation(); }
		const Vector3& GetScale() const { return Transform.GetScale(); }

	protected:
		Str::FString Name;
		Transform Transform;

		std::shared_ptr<Collision::Collider> Collider;
		Collision::RigidBody* RigidBody;
	};
}
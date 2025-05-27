#pragma once
#include "Collider.h"

namespace Collision
{
	class COLLISION_API CollisionManager
	{
	public:
		CollisionManager()
			: CollisionCheckWhether{ 0 }
			, CurrentMappingPoint(0)
		{}
		~CollisionManager() = default;

	public:
		void TypeMapping(const Str::FString& _ColliderType)
		{
			auto Iter = TypeMappingTable.find(_ColliderType);
			if (Iter != TypeMappingTable.end())
				return;

			if (TypeMappingTable.size() >= 32)
				return;

			TypeMappingTable.insert(std::make_pair(_ColliderType, CurrentMappingPoint++));
		}

		RectCollider* GetRectCollider(const Str::FString& _ColliderType)
		{
			auto Iter = TypeMappingTable.find(_ColliderType);
			if (Iter == TypeMappingTable.end())
				return nullptr;

			RectCollider* Collider = new RectCollider;
			Collider->SetColliderType(Iter->second);
			RectColliders.push_back(Collider);

			return Collider;
		}

		CircleCollider* GetCircleCollider(const Str::FString& _ColliderType)
		{
			auto Iter = TypeMappingTable.find(_ColliderType);
			if (Iter == TypeMappingTable.end())
				return nullptr;

			CircleCollider* Collider = new CircleCollider;
			Collider->SetColliderType(Iter->second);
			CircleColliders.push_back(Collider);

			return Collider;
		}

		void CheckCollisionWhether(const Str::FString& _Type1, const Str::FString& _Type2)
		{
			uint32_t ColliderType1 = 0;
			uint32_t ColliderType2 = 0;
			auto Iter = TypeMappingTable.find(_Type1);
			if (Iter == TypeMappingTable.end())
				return;

			ColliderType1 = Iter->second;
			Iter = TypeMappingTable.find(_Type2);
			if (Iter == TypeMappingTable.end())
				return;
			ColliderType2 = Iter->second;

			uint32_t i = 1 << ColliderType2;
			CollisionCheckWhether[ColliderType1] |= i;

			i = 1 << ColliderType1;
			CollisionCheckWhether[ColliderType2] |= i;
		}
		
	private:
		std::list<RectCollider*> RectColliders;
		std::list<CircleCollider*> CircleColliders;

		std::map<Str::FString, uint32_t> TypeMappingTable;
		uint32_t CurrentMappingPoint;

		uint32_t CollisionCheckWhether[sizeof(uint32_t)];
	};

	
	class COLLISION_API CollisionDetector
	{
	public:
		
	private:
		
	};
}


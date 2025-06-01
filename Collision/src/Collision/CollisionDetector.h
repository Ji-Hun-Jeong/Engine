#pragma once
#include <random>

#include "Collider.h"

namespace Collision
{
	class COLLISION_API CollisionIdGenerator
	{
	public:
		CollisionIdGenerator() 
			: Generator(RandomDevice())
			, Distribution(0, UINT32_MAX)
		{}
		~CollisionIdGenerator() {}

	public:
		uint32_t GetColliderId()
		{
			uint32_t Id = Distribution(Generator);
			if (ColliderIds.find(Id) == ColliderIds.end())
			{
				ColliderIds.insert(Id);
				return Id;
			}

			return GetColliderId();
		}
		void EraseColliderId(uint32_t _Id)
		{
			ColliderIds.erase(_Id);
		}

	private:
		std::set<uint32_t> ColliderIds;

		std::random_device RandomDevice;
		std::mt19937 Generator;
		std::uniform_int_distribution<uint32_t> Distribution;

	};

	class COLLISION_API ColliderManager
	{
		friend class CollisionDetector;
	public:
		ColliderManager()
			: CollisionCheckWhether{ 0 }
			, CurrentMappingPoint(0)
		{}
		~ColliderManager() = default;

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

		void BindCollisionWhether(const Str::FString& _Type1, const Str::FString& _Type2)
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

		uint32_t GetTypeByString(const Str::FString& _Type)
		{
			auto Iter = TypeMappingTable.find(_Type);
			if (Iter == TypeMappingTable.end())
				return UINT32_MAX;
			return Iter->second;
		}

		std::shared_ptr<RectCollider> GetRectCollider(const Str::FString& _ColliderType)
		{
			auto Iter = TypeMappingTable.find(_ColliderType);
			if (Iter == TypeMappingTable.end())
				return nullptr;

			std::shared_ptr<RectCollider> Collider = std::make_shared<RectCollider>();
			Collider->SetColliderId(IdGenerator.GetColliderId());
			Collider->SetColliderType(Iter->second);
			RectColliders.push_back(Collider);

			return Collider;
		}

		std::shared_ptr<CircleCollider> GetCircleCollider(const Str::FString& _ColliderType)
		{
			auto Iter = TypeMappingTable.find(_ColliderType);
			if (Iter == TypeMappingTable.end())
				return nullptr;

			std::shared_ptr<CircleCollider> Collider = std::make_shared<CircleCollider>();
			Collider->SetColliderId(IdGenerator.GetColliderId());
			Collider->SetColliderType(Iter->second);
			CircleColliders.push_back(Collider);

			return Collider;
		}

	private:
		bool checkCollisionWhether(uint8_t _Type1, uint8_t _Type2)
		{
			uint32_t i = 1 << _Type2;
			if (CollisionCheckWhether[_Type1] & i)
				return true;
			i = 1 << _Type1;
			if (CollisionCheckWhether[_Type2] & i)
				return true;

			return false;
		}

	private:
		std::list<std::shared_ptr<RectCollider>> RectColliders;
		std::list<std::shared_ptr<CircleCollider>> CircleColliders;

		std::map<Str::FString, uint32_t> TypeMappingTable;
		uint32_t CurrentMappingPoint;

		uint32_t CollisionCheckWhether[32];

		CollisionIdGenerator IdGenerator;

	};

	
	class COLLISION_API CollisionDetector
	{
	public:
		CollisionDetector(ColliderManager& _ColliderMgr)
			: ColliderMgr(_ColliderMgr)
		{}
		~CollisionDetector() = default;

	public:
		void CheckCollisionProcessing()
		{
			checkSameCollisionGroup<RectCollider, RectCollider>(ColliderMgr.RectColliders, ColliderMgr.RectColliders);
			checkOtherCollisionGroup<RectCollider, CircleCollider>(ColliderMgr.RectColliders, ColliderMgr.CircleColliders);
			checkSameCollisionGroup<CircleCollider, CircleCollider>(ColliderMgr.CircleColliders, ColliderMgr.CircleColliders);

			eraseCollider(ColliderMgr.RectColliders);
			eraseCollider(ColliderMgr.CircleColliders);
		}

	private:
		template <typename T_Collider1, typename T_Collider2>
		void checkSameCollisionGroup(std::list<std::shared_ptr<T_Collider1>>& _ColliderList1, std::list<std::shared_ptr<T_Collider2>>& _ColliderList2)
		{
			if (_ColliderList2.empty())
				return;

			size_t ForwardCount = 1;
			for (auto Iter1 = _ColliderList1.begin(); Iter1 != _ColliderList1.end(); ++Iter1)
			{
				auto Iter2 = _ColliderList2.begin();
				std::advance(Iter2, ForwardCount++);

				if (Iter2 == _ColliderList2.end())
					continue;

				for (; Iter2 != _ColliderList2.end(); ++Iter2)
				{
					checkCollision((*Iter1).get(), (*Iter2).get());
				}
			}
		}
		template <typename T_Collider1, typename T_Collider2>
		void checkOtherCollisionGroup(std::list<std::shared_ptr<T_Collider1>>& _ColliderList1, std::list<std::shared_ptr<T_Collider2>>& _ColliderList2)
		{
			for (auto Iter1 = _ColliderList1.begin(); Iter1 != _ColliderList1.end(); ++Iter1)
			{
				for (auto Iter2 = _ColliderList2.begin(); Iter2 != _ColliderList2.end(); ++Iter2)
				{
					if ((*Iter1)->GetColliderId() == (*Iter2)->GetColliderId())
						continue;
					checkCollision((*Iter1).get(), (*Iter2).get());
				}
			}
		}

		union UCollisionPair
		{
			struct
			{
				uint32_t Id1;
				uint32_t Id2;
			}Key;
			uint64_t Value;
		};

		template <typename T_Collider1, typename T_Collider2>
		void checkCollision(T_Collider1* _Collider1, T_Collider2* _Collider2)
		{
			uint8_t Collider1Type = _Collider1->GetColliderType();
			uint8_t Collider2Type = _Collider2->GetColliderType();
			if (ColliderMgr.checkCollisionWhether(Collider1Type, Collider2Type) == false)
				return;

			uint32_t Collider1Id = _Collider1->GetColliderId();
			uint32_t Collider2Id = _Collider2->GetColliderId();

			UCollisionPair CollisionPair;
			if (Collider1Id < Collider2Id)
			{
				CollisionPair.Key.Id1 = Collider1Id;
				CollisionPair.Key.Id2 = Collider2Id;
			}
			else
			{
				CollisionPair.Key.Id1 = Collider2Id;
				CollisionPair.Key.Id2 = Collider1Id;
			}

			auto Iter = CollisionValues.find(CollisionPair.Value);

			if (IsCollision(_Collider1, _Collider2))	// 이번 프레임에 충돌
			{
				if (Iter == CollisionValues.end())		// 이전 프레임에서도 충돌안함
				{
					_Collider1->OnCollisionEnter(_Collider2);
					_Collider2->OnCollisionEnter(_Collider1);
					CollisionValues.insert(CollisionPair.Value);
				}
				else									// 이전 프레임에서는 충돌함
				{
					_Collider1->OnCollisionStay(_Collider2);
					_Collider2->OnCollisionStay(_Collider1);
				}
			}
			else										// 이번 프레임에 충돌안함
			{
				if (Iter != CollisionValues.end())		// 근데 이전프레임에서는 충돌했음
				{
					_Collider1->OnCollisionExit(_Collider2);
					_Collider2->OnCollisionExit(_Collider1);
					CollisionValues.erase(Iter);
				}
			}
		}

		template <typename T_Collider>
		void eraseCollider(std::list<std::shared_ptr<T_Collider>>& _List)
		{
			for (auto Iter = _List.begin(); Iter != _List.end();)
			{
				auto ColliderPtr = *Iter;
				if (ColliderPtr.use_count() == 1)
				{
					ColliderMgr.IdGenerator.EraseColliderId(ColliderPtr->GetColliderId());
					ColliderPtr.reset();
					Iter = _List.erase(Iter);
				}
				else
					++Iter;
			}
		}

	private:
		ColliderManager& ColliderMgr;

		std::set<uint64_t> CollisionValues;

	};
}


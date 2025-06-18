#pragma once
#include "Object/Actor.h"

namespace Game
{
	class Monster : public Actor
	{
		using Super = Actor;
		CLONE(Monster, Actor)
	public:
		Monster(const Str::FString& _Name)
			: Super(_Name)
		{}
		Monster(const Monster& _Other)
			: Super(_Other)
		{}
		Monster(Monster&& _Other) = delete;
		Monster& operator = (const Monster& _Other) = delete;
		Monster& operator = (Monster&& _Other) = delete;
		~Monster() = default;

	public:
		
	};
}



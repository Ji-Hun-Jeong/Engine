#pragma once
#include "Object/Actor.h"

namespace Game
{
	class BackGround : public Actor
	{
		using Super = Actor;
		CLONE(BackGround, Actor)
	public:
		BackGround(const Str::FString& _Name)
			: Super(_Name)
		{}
		~BackGround() {}
	};
}



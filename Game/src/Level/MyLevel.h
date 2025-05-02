#pragma once
#include "Level/Level.h"

namespace Game
{
	class MyLevel : public Level
	{
		using Super = Level;
	public:
		explicit MyLevel(Graphics::IDRGenerator& _Generator);
		~MyLevel();

	public:
		void InitLevel() override;
		void EnterLevel() override;
		void Update() override;
		void ExitLevel() override;

	private:

	};
}



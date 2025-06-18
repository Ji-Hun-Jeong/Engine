#include "pch.h"
#include "Class.h"

#include "Class/Phantom/Phantom.h"

namespace Game
{
	ClassManager::ClassManager()
		: PlayerClass(nullptr)
	{
		registClass(new Phantom);
	}
}
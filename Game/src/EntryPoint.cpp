#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "pch.h"
#include "App/Game.h"
#include "Core/Core.h"

int main(int argc, char** argv)
{
	// 콘솔종료는 비정상종료
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	
	Game* MyGame = new Game(1280, 720);
	
	Engine::Core Core(MyGame);

	if (Core.Init() == false)
		return -1;

	return Core.Run();
}
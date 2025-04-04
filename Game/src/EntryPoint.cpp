#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "pch.h"
#include "App/Game.h"
#include "Core/Core.h"
#include "Platform/DirectX/DX.h"

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#pragma comment(lib, "dxguid.lib")

#ifdef _DEBUG
void list_remaining_d3d_objects()
{
	HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));

	IDXGIDebug* debug;

	GetDebugInterface(IID_PPV_ARGS(&debug));

	OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
	OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");

	debug->Release();
}
#endif
int main(int argc, char** argv)
{
	// 콘솔종료는 비정상종료
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	
	GameWorld* MyGame = new GameWorld(1280, 720);
	
	Engine::Core Core(MyGame);

	Core.Init();

	int i = Core.Run();
	list_remaining_d3d_objects();
	return i;
}
#pragma once
#include "Renderer/src/Render/ModelRegistry.h"
#include "Renderer/src/Platform/DirectX/DX.h"
#include "Renderer/src/Interface/IRenderTargetView.h"
#include "Renderer/src/Interface/IViewPort.h"
#include "Renderer/src/Interface/IVertexShaderInputLayout.h"
#include "Renderer/src/Interface/IPixelShader.h"
#include "Renderer/src/Interface/ISampler.h"
#include "Renderer/src/Interface/IRasterizerState.h"
#include "Renderer/src/Interface/IDepthStencilState.h"
#include "Renderer/src/Interface/ITopology.h"
#include "Renderer/src/Interface/IDraw.h"

namespace Graphics
{
	// ComPtr는 stl의 스마트포인터와 작동방식이 조금 다름
	// 아마 ComPtr가 가리킬수 있는 Com객체는 자기 자신이 RefCount를 관리함.
	// ComPtr는 그 RefCount를 생성될 때 증가, 삭제될 때 감소 시켜주는 역할을 할 뿐임
	// 그래서 쌩 포인터로도 객체의 RefCount를 관리할 수 있음 -> 직접 AddRef(), Release() 호출
	// 하지만 지역변수로 Com객체를 사용할 때는 웬만하면 ComPtr를 사용..... 맞나?
	// A객체가 Com객체를 쌩포인터로 들고있어도 참조카운트만 잘 조절해주면 A객체가 소멸되기 전까지 그 Com객체는 절대 안사라짐

	// stl의 스마트포인터는 스마트포인터 객체가 참조 카운트를 관리하여 외부에 있는 스마트포인터 객체를 쌩포인터로 받았다가는
	// 그 객체의 생명주기(참조 카운트)를 관리할 수 없기 때문에 위험할 수 있음
	// B객체가 쌩포인터로 shared_ptr<A>객체의 get()을 들고있었는데 이때 그 객체를 참조하고 있다는 RefCount를 바꿀 방법이 없음
	// 따라서 A객체가 외부에서 삭제될 경우 B객체는 지워진 메모리를 가리킴

	// 즉, 생명주기를 쌩포인터로도 가리킬 수 있는 Com객체 같은 경우는 자신있으면 쌩포인터로 들고있어도 됌
	// 하지만 생명주기를 스마트포인터에 의존해야하는 일반객체 같은 경우는 만약 멤버로 들고있을 예정이라면 스마트포인터를 사용하는게 좋음
	// 만약 멤버에 대입하지 않을꺼고 함수 내부에서만 사용할 예정이면 쌩포인터로 받아도됌
	class IDRGenerator
	{
	public:
		IDRGenerator(HWND _WindowHandle)
			: WindowHandle(_WindowHandle)
		{
			RECT r = { 0 };
			::GetWindowRect(WindowHandle, &r);
			ScreenWidth = r.right - r.left;
			ScreenHeight = r.bottom - r.top;
		}
		virtual ~IDRGenerator() = 0 {}

	public:
		virtual RefCounterPtr<IRenderTargetView> GenerateMainRenderTargetView() = 0;
		virtual RefCounterPtr<IViewPort> GenerateMainViewPort() = 0;
		virtual RefCounterPtr<IModel> GenerateModel(void* _VertexData, size_t _VertexSize, size_t _NumOfVertex
			, void* _IndexData, size_t _IndexSize, size_t _NumOfIndex) = 0;
		virtual RefCounterPtr<IVertexShader> GenerateVertexShaderAndInputLayout(const Str::FString& _Path
			, const std::vector<InputElementDesc>& _InputElements) = 0;
		virtual RefCounterPtr<IPixelShader> GeneratePixelShader(const Str::FString& _Path) = 0;
		virtual RefCounterPtr<ISampler> GenerateLinearSampler() = 0;
		virtual RefCounterPtr<IRasterizerState> GenerateSolidCWState() = 0;
		virtual RefCounterPtr<IDepthStencilState> GenerateBasicDepthStencilState() = 0;
		virtual RefCounterPtr<IConstBuffer> GenerateConstBuffer(const std::vector<CpuConstData>& _CpuData) = 0;
		virtual RefCounterPtr<ITopology> GenerateTopology(eTopology _Topology) = 0;
		virtual RefCounterPtr<IDraw> GenerateDrawer() = 0;
		
		ModelRegistry& GetRegistry() { return ModelRegistry; }
		/*void LoadSRV(const Str::FString& _Path, const Str::FString& _ImageName) override
		{
			if (Resource.Images.find(_ImageName) != Resource.Images.end())
				return;

			std::wstring WPath = _Path.GetWString();
			ID3D11ShaderResourceView* Image = nullptr;
			HRESULT HR = DirectX::CreateWICTextureFromFile(Resource.Device.Get(), WPath.c_str(), nullptr, &Image);
			if (FAILED(HR))
				assert(0);

			Resource.Images.insert(std::make_pair(_ImageName, Image));
			Image->Release();
		}*/

	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;

		ModelRegistry ModelRegistry;
	};

}



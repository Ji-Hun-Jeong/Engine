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
	// ComPtr�� stl�� ����Ʈ�����Ϳ� �۵������ ���� �ٸ�
	// �Ƹ� ComPtr�� ����ų�� �ִ� Com��ü�� �ڱ� �ڽ��� RefCount�� ������.
	// ComPtr�� �� RefCount�� ������ �� ����, ������ �� ���� �����ִ� ������ �� ����
	// �׷��� �� �����ͷε� ��ü�� RefCount�� ������ �� ���� -> ���� AddRef(), Release() ȣ��
	// ������ ���������� Com��ü�� ����� ���� �����ϸ� ComPtr�� ���..... �³�?
	// A��ü�� Com��ü�� �������ͷ� ����־ ����ī��Ʈ�� �� �������ָ� A��ü�� �Ҹ�Ǳ� ������ �� Com��ü�� ���� �Ȼ����

	// stl�� ����Ʈ�����ʹ� ����Ʈ������ ��ü�� ���� ī��Ʈ�� �����Ͽ� �ܺο� �ִ� ����Ʈ������ ��ü�� �������ͷ� �޾Ҵٰ���
	// �� ��ü�� �����ֱ�(���� ī��Ʈ)�� ������ �� ���� ������ ������ �� ����
	// B��ü�� �������ͷ� shared_ptr<A>��ü�� get()�� ����־��µ� �̶� �� ��ü�� �����ϰ� �ִٴ� RefCount�� �ٲ� ����� ����
	// ���� A��ü�� �ܺο��� ������ ��� B��ü�� ������ �޸𸮸� ����Ŵ

	// ��, �����ֱ⸦ �������ͷε� ����ų �� �ִ� Com��ü ���� ���� �ڽ������� �������ͷ� ����־ ��
	// ������ �����ֱ⸦ ����Ʈ�����Ϳ� �����ؾ��ϴ� �Ϲݰ�ü ���� ���� ���� ����� ������� �����̶�� ����Ʈ�����͸� ����ϴ°� ����
	// ���� ����� �������� �������� �Լ� ���ο����� ����� �����̸� �������ͷ� �޾Ƶ���
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



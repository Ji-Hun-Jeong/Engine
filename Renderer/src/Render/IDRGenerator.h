#pragma once
#include "Interface/IMesh.h"
#include "Interface/IConstBuffer.h"
#include "Interface/IRenderTargetView.h"
#include "Interface/IViewPort.h"
#include "Interface/IVertexShaderInputLayout.h"
#include "Interface/IPixelShader.h"
#include "Interface/ISampler.h"
#include "Interface/IRasterizerState.h"
#include "Interface/IDepthStencilState.h"
#include "Interface/IShaderResource.h"
#include "Interface/ITopology.h"
#include "Interface/IDraw.h"

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
	class RENDERER_API IDRGenerator
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
		virtual RefCounterPtr<IMesh> GenerateMesh(void* _VertexData, size_t _VertexSize, size_t _NumOfVertex
			, void* _IndexData, size_t _IndexSize, size_t _NumOfIndex) = 0;
		virtual RefCounterPtr<IVertexShader> GenerateVertexShaderAndInputLayout(const Str::FString& _Path
			, const std::vector<InputElementDesc>& _InputElements) = 0;
		virtual RefCounterPtr<IPixelShader> GeneratePixelShader(const Str::FString& _Path) = 0;
		virtual RefCounterPtr<ISampler> GenerateLinearSampler() = 0;
		virtual RefCounterPtr<IRasterizerState> GenerateSolidCWState() = 0;
		virtual RefCounterPtr<IDepthStencilState> GenerateBasicDepthStencilState() = 0;
		virtual RefCounterPtr<IConstBuffer> GenerateConstBuffer(const std::vector<CpuConstData>& _CpuData) = 0;
		virtual RefCounterPtr<ITopology> GenerateTopology(eTopology _Topology) = 0;
		virtual RefCounterPtr<IPresenter> GeneratePresenter() = 0;
		virtual RefCounterPtr<IShaderResource> GenerateShaderResource(const std::vector<Str::FString>& _Paths) = 0;

	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;

	};

}



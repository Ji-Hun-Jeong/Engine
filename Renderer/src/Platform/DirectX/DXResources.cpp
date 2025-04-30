#include "pch.h"
#include "DXResources.h"

namespace Graphics
{
	namespace DX
	{
		using Microsoft::WRL::ComPtr;

		DXResource::DXResource()
			: ViewPort{}
			, NumOfMultiSamplingLevel(0)
		{
			
		}

		DXResource::~DXResource()
		{
			for (auto& vs : VertexShader)
				vs.Reset();
			for (auto& il : InputLayout)
				il.Reset();
			for (auto& ps : PixelShader)
				ps.Reset();
			for (auto& ss : SamplerState)
				ss.Reset();
			for (auto& rs : RasterizerState)
				rs.Reset();
			for (auto& dss : DepthStencilState)
				dss.Reset();
			for (auto& dsv : DepthStencilView)
				dsv.Reset();
			for (auto& rtv : RenderTargetView)
				rtv.Reset();
			for (auto iter = DXBuffers.begin(); iter != DXBuffers.end();)
			{
				delete iter->second;
				iter = DXBuffers.erase(iter);
			}
			for (auto& SRV : Images)
				SRV.second.Reset();
		}

		void DXResource::Initalize()
		{
			InitShader();
			InitSampler();
			InitRS();
			InitDSS();
		}

		void DXResource::InitShader()
		{
			ComPtr<ID3DBlob> shaderBlob;
			ComPtr<ID3DBlob> errorBlob;

			UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
			compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

			HRESULT hr = D3DCompileFromFile(
				L"./Renderer/resource/Shader/ColorVS.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
				"vs_5_0", compileFlags, 0, &shaderBlob, &errorBlob);
			if (FAILED(hr))	assert(0);

			hr = Device->CreateVertexShader(shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(), NULL,
				VertexShader[(UINT)eCategoryVS::Color].GetAddressOf());
			if (FAILED(hr))	assert(0);

			std::vector<D3D11_INPUT_ELEMENT_DESC> basicInputElements =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
					D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3,
					D3D11_INPUT_PER_VERTEX_DATA, 0}
			};

			hr = Device->CreateInputLayout(basicInputElements.data(), UINT(basicInputElements.size()),
				shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(), InputLayout[(UINT)eCategoryIL::Basic].GetAddressOf());
			if (FAILED(hr))	assert(0);

			hr = D3DCompileFromFile(
				L"./Renderer/resource/Shader/ColorPS.hlsl", 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
				"ps_5_0", compileFlags, 0, &shaderBlob, &errorBlob);
			if (FAILED(hr))	assert(0);

			hr = Device->CreatePixelShader(shaderBlob->GetBufferPointer(),
				shaderBlob->GetBufferSize(), NULL,
				PixelShader[(UINT)eCategoryPS::Color].GetAddressOf());
			if (FAILED(hr))	assert(0);

		}
		void DXResource::InitSampler()
		{
			D3D11_SAMPLER_DESC sampDesc;
			ZeroMemory(&sampDesc, sizeof(sampDesc));
			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
			HRESULT hr = Device->CreateSamplerState(&sampDesc, SamplerState[(UINT)eCategorySS::Linear].GetAddressOf());
			if (FAILED(hr))
				assert(0);
		}
		void DXResource::InitRS()
		{
			D3D11_RASTERIZER_DESC RDesc;
			ZeroMemory(&RDesc, sizeof(RDesc));
			RDesc.FillMode = D3D11_FILL_SOLID;	// WireFrame
			RDesc.CullMode = D3D11_CULL_BACK;	// None, Front
			RDesc.FrontCounterClockwise = false;
			RDesc.DepthClipEnable = true;
			RDesc.MultisampleEnable = true;
			HRESULT hr = Device->CreateRasterizerState(&RDesc, RasterizerState[(UINT)eCategoryRS::SolidCw].GetAddressOf());
			if (FAILED(hr)) assert(0);

		}
		void DXResource::InitDSS()
		{
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			depthStencilDesc.DepthEnable = true; // false
			depthStencilDesc.DepthWriteMask =
				D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc =
				D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

			HRESULT hr = Device->CreateDepthStencilState(&depthStencilDesc, DepthStencilState[(UINT)eCategoryDSS::Basic].GetAddressOf());
			if (FAILED(hr)) assert(0);
		}

	}
}
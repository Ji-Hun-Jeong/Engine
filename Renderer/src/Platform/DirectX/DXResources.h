#pragma once
#include "DX.h"

namespace Graphics
{
	using Microsoft::WRL::ComPtr;
	struct DXBuffers
	{
		ComPtr<ID3D11Buffer> VertexBuffer;
		ComPtr<ID3D11Buffer> IndexBuffer;
		UINT Stride;
	};
	namespace DXResource
	{
		extern ComPtr<ID3D11VertexShader> VertexShader[(UINT)eCategoryVS::End];
		extern ComPtr<ID3D11InputLayout> InputLayout[(UINT)eCategoryIL::End];
		extern ComPtr<ID3D11PixelShader> PixelShader[(UINT)eCategoryPS::End];
		extern ComPtr<ID3D11SamplerState> SamplerState[(UINT)eCategorySS::End];
		
		extern D3D11_VIEWPORT ViewPort[(UINT)eCategoryVP::End];
		extern ComPtr<ID3D11RasterizerState> RasterizerState[(UINT)eCategoryRS::End];
		extern ComPtr<ID3D11DepthStencilState> DepthStencilState[(UINT)eCategoryDSS::End];
		extern ComPtr<ID3D11DepthStencilView> DepthStencilView[(UINT)eCategoryDSV::End];
		extern ComPtr<ID3D11RenderTargetView> RenderTargetView[(UINT)eCategoryRTV::End];
		
		extern std::unordered_map<std::string, struct DXBuffers*> DXBuffers;
		
		extern void InitResource(ID3D11Device* _Device);
		extern void InitShader(ID3D11Device* _Device);
		extern void InitSampler(ID3D11Device* _Device);
		extern void InitRS(ID3D11Device* _Device);
		extern void InitDSS(ID3D11Device* _Device);
		extern void AddRTV(eCategoryRTV _CategoryRTV, ID3D11RenderTargetView* _RTV);
		extern void AddDSV(eCategoryDSV _CategoryDSV, ID3D11DepthStencilView* _DSV);
	};
}



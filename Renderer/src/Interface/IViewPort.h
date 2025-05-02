#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	class IViewPort : public RefCounter
	{
	public:
		IViewPort() = default;
		virtual ~IViewPort() = default;

	public:
		virtual void RSSetViewPort() = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXViewPort : public IViewPort
		{
		public:
			DXViewPort(ComPtr<ID3D11DeviceContext>& _Context, const std::vector<D3D11_VIEWPORT>& _VP)
				: Context(_Context)
				, ViewPorts{}
			{
				for (auto& VP : _VP)
					ViewPorts.push_back(VP);
			}
			~DXViewPort()
			{}

		public:
			void RSSetViewPort() override
			{
				Context->RSSetViewports(ViewPorts.size(), ViewPorts.data());
			}

		private:
			std::vector<D3D11_VIEWPORT> ViewPorts;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}


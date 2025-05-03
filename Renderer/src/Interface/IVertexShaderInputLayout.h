#pragma once
#include "Platform/DirectX/DX.h"

namespace Graphics
{
	enum class eSementicName
	{
		Position, Color,
	};
	enum class eFormat
	{
		Vector3,
	};
	enum class eInputClass
	{
		VertexData,
	};
	struct InputElementDesc
	{
		eSementicName SementicName;
		eFormat Format;
		UINT Offset;
		eInputClass InputClass;
	};

	class IVertexShader : public RefCounter
	{
	public:
		IVertexShader() = default;
		virtual ~IVertexShader() = default;

	public:
		virtual void VSSetShader() const = 0;
		virtual void IASetInputLayout() const = 0;

	protected:

	};

	namespace DX
	{
		using Microsoft::WRL::ComPtr;
		class DXVertexShader : public IVertexShader
		{
		public:
			DXVertexShader(ComPtr<ID3D11DeviceContext>& _Context, ComPtr<ID3D11VertexShader>& _VS, ComPtr<ID3D11InputLayout>& _IL)
				: Context(_Context)
				, VertexShader(_VS.Get())
				, InputLayout(_IL.Get())
			{
				VertexShader->AddRef();
				InputLayout->AddRef();
			}
			~DXVertexShader()
			{
				VertexShader->Release();
				InputLayout->Release();
			}

		public:
			void VSSetShader() const override
			{
				Context->VSSetShader(VertexShader, nullptr, 0);
			}
			void IASetInputLayout() const override
			{
				Context->IASetInputLayout(InputLayout);
			}

		private:
			ID3D11VertexShader* VertexShader;
			ID3D11InputLayout* InputLayout;
			ComPtr<ID3D11DeviceContext>& Context;
		};
	}

}


#pragma once
#include "Render/IDRGenerator.h"

namespace Graphics
{
	class PixelCollisionProcess;
	class RENDERER_API PixelCollisionInterface
	{
	public:
		PixelCollisionInterface(PixelCollisionProcess& _Processor, UINT _Index, Vector3& _Position, std::function<void(int)> _CollisionEvent)
			: Index(_Index), Position(_Position), CollisionEvent(_CollisionEvent), Processor(_Processor)
		{}
		~PixelCollisionInterface() {}

	public:
		UINT GetIndex() const { return Index; }
		const Vector3& GetPosition() const { return Position; }

		void SetPosition(const Vector3& _Position) { Position = _Position; }
		void SetActive(bool _TF);

	private:
		UINT Index;
		Vector3& Position;
		std::function<void(int)> CollisionEvent;

		PixelCollisionProcess& Processor;
	};

	class RENDERER_API PixelCollisionProcess
	{
	public:
		PixelCollisionProcess(IDRGenerator& _Generator)
		{
			for (int i = 0; i < 64; ++i)
				RemainIndex.push(i);

			std::vector<BufferDesc> BufferDescs =
			{
				{Positions.data(), sizeof(Vector3), UINT(Positions.size())},
				{CollisionWhethers.data(), sizeof(int), UINT(CollisionWhethers.size())},
				{CollisionStates.data(), sizeof(int), UINT(CollisionStates.size())}
			};
			UAV = _Generator.GenerateUnorderedAccessView(BufferDescs);

			ComputeShader = _Generator.GenerateComputeShader("./Renderer/resource/Shader/PixelCollisionCS.hlsl");
		}
		~PixelCollisionProcess() {}

	public:
		PixelCollisionInterface* RegistPixelCollision(Vector3& _Position, std::function<void(int)> _CollisionEvent = nullptr)
		{
			int Index = RemainIndex.top();
			RemainIndex.pop();

			CollisionWhethers[Index] = true;

			PixelCollisionInterface* CollisionInterface = new PixelCollisionInterface(*this, Index, _Position, _CollisionEvent);
			CollisionInterfaces.insert(CollisionInterface);
			return CollisionInterface;
		}

		void RemovePixelCollision(PixelCollisionInterface* _CollisionInterface)
		{
			UINT Index = _CollisionInterface->GetIndex();
			RemainIndex.push(Index);

			CollisionInterfaces.erase(_CollisionInterface);
		}

		void Progress()
		{
			for (auto Iter = CollisionInterfaces.begin(); Iter != CollisionInterfaces.end(); ++Iter)
			{
				PixelCollisionInterface* Interface = *Iter;
				UINT Index = Interface->GetIndex();
				Positions[Index] = Interface->GetPosition();
			}
			UAV->UploadBuffer(0, { Positions.data(), sizeof(Vector3), UINT(Positions.size()) });
			UAV->UploadBuffer(1, { CollisionWhethers.data(), sizeof(int), UINT(CollisionWhethers.size()) });
			UAV->UploadBuffer(2, { CollisionStates.data(), sizeof(int), UINT(CollisionStates.size()) });

			ComputeShader->CSSetShader();

			UAV->CSSetUnorderedAccessViews(0);

			ComputeShader->Dispatch(64, 1, 1);
			ComputeShader->ComputeShaderBarrier();

			// 여기서 다시 cpu로 복사

			UAV->DownloadBuffer(0, { Positions.data(), sizeof(Vector3), UINT(Positions.size()) });
			UAV->DownloadBuffer(1, { CollisionWhethers.data(), sizeof(int), UINT(CollisionWhethers.size()) });
			UAV->DownloadBuffer(2, { CollisionStates.data(), sizeof(int), UINT(CollisionStates.size()) });

			for (auto Iter = CollisionInterfaces.begin(); Iter != CollisionInterfaces.end(); ++Iter)
			{
				PixelCollisionInterface* Interface = *Iter;
				UINT Index = Interface->GetIndex();
				Interface->SetPosition(Positions[Index]);
			}
		}

		void SetActiveInterface(UINT _Index, bool _TF)
		{
			CollisionWhethers[_Index] = _TF;
		}
	private:
		

	private:
		std::set<PixelCollisionInterface*> CollisionInterfaces;

		std::array<Vector3, 64> Positions;
		std::array<int, 64> CollisionWhethers;
		std::array<int, 64> CollisionStates;
		RefCounterPtr<IUnorderedAccessView> UAV;

		RefCounterPtr<IComputeShader> ComputeShader;

		std::priority_queue<int, std::vector<int>, std::greater<int>> RemainIndex;

	};

}



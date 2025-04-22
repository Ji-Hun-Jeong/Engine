#pragma once
#include "Component/Transform/Transform.h"

namespace Game
{
	class Object
	{
	public:
		Object(const Str::FString& _Name);
		Object(const Object& _Other);
		Object(Object&& _Other) = delete;
		Object& operator = (const Object& _Other) = delete;
		Object& operator = (Object&& _Other) = delete;
		virtual ~Object();

	public:
		virtual Object* GetClone() const = 0;
		virtual void InitObject();
		virtual void Update();
		virtual void Destory();

		void SetName(const Str::FString& _Name) { Name = _Name; }
		const Str::FString& GetName() const { return Name; }

		void SetTransform(Transform* _Transform) { Transform = _Transform; }

	protected:
		Str::FString Name;
		Transform* Transform;

	};
}
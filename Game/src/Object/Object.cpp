#include "pch.h"
#include "Object.h"

namespace Game
{
	Object::Object(const Str::FString& _Name)
		: Name(_Name)
		, Transform()
		, Collider(nullptr)
		, RigidBody(nullptr)
	{
	}
	Object::Object(const Object& _Other)
		: Name(_Other.Name)
		, Transform()
		, Collider(nullptr)
		, RigidBody(nullptr)
	{
	}
	Object::~Object()
	{
		if (RigidBody)
			delete RigidBody;
	}
	void Object::InitObject()
	{
	}
	void Object::Update()
	{
		if (RigidBody)
			RigidBody->Update(Time::GetDT());
	}
	void Object::PostUpdate()
	{
		if (Collider)
			Collider->SetPosition(Transform.GetPosition());
	}
	void Object::Destory()
	{
	}
}
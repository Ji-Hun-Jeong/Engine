#include "pch.h"
#include "Object.h"

namespace Game
{
	Object::Object(const Str::FString& _Name)
		: Name(_Name)
		, Transform()
		, Collider(nullptr)
	{
	}
	Object::Object(const Object& _Other)
		: Name(_Other.Name)
		, Transform()
		, Collider(nullptr)
	{
	}
	Object::~Object()
	{
		
	}
	void Object::InitObject()
	{
	}
	void Object::Update()
	{
		
	}
	void Object::Destory()
	{
	}
}
#include "pch.h"
#include "Object.h"

namespace Game
{
	Object::Object(const Str::FString& _Name)
		: Name(_Name)
	{
	}
	Object::Object(const Object& _Other)
		: Name(_Other.Name)
	{
	}
	Object::~Object()
	{
		if (Transform)
			delete Transform;
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
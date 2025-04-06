#include "pch.h"
#include "Object.h"

namespace Game
{
	Object::Object(const std::string& _Name)
		: Name(_Name)
	{
	}
	Object::Object(const Object& _Other)
		: Name(_Other.Name)
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
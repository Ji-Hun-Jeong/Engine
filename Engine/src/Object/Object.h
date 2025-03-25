#pragma once

namespace Engine
{
	class Object
	{
	public:
		Object(const std::string& _Name);
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

		void SetName(const std::string& _Name) { Name = _Name; }
		const std::string& GetName() const { return Name; }

	protected:
		std::string Name;
	};
}
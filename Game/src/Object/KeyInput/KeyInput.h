#pragma once
#include <Engine/src/Input/Input.h>

namespace Game
{
	class KeyValue
	{
		friend class KeyInput;
	public:
		KeyValue(Input::eKeyType _KeyType, Input::eButtonState _KeyState, std::function<void()> _KeyEvent)
			: KeyType(_KeyType), KeyState(_KeyState), KeyEvent(_KeyEvent)
		{}
		~KeyValue() = default;

	public:
		void GenerateEvent()
		{
			KeyEvent();
		}

	private:
		Input::eKeyType KeyType;
		Input::eButtonState KeyState;

		std::function<void()> KeyEvent;

	};

	class KeyInput
	{
	public:
		KeyInput()
			: IsFocus(true)
		{}
		KeyInput(const KeyInput&) = delete;
		~KeyInput();

	public:
		void UpdateKeyState();

		void AddKey(const Str::FString& _KeyName, Input::eKeyType _KeyType, Input::eButtonState _KeyState, std::function<void()> _KeyEvent);

		void SetFocus(bool _IsFocus) { IsFocus = _IsFocus; }
		
	private:
		std::unordered_map<Str::FString, KeyValue*> KeyValues;

		bool IsFocus;
	};

}


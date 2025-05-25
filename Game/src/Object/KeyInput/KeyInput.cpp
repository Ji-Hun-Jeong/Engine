#include "pch.h"
#include "KeyInput.h"

namespace Game
{
	KeyInput::~KeyInput()
	{
		for (auto& Iter : KeyValues)
			delete Iter.second;
	}

	void KeyInput::UpdateKeyState()
	{
		if (IsFocus == false)
			return;

		for (auto& Iter : KeyValues)
		{
			KeyValue* KeyValue = Iter.second;
			Input::eKeyType KeyType = KeyValue->KeyType;
			Input::eButtonState KeyState = KeyValue->KeyState;

			if (Input::GetKey(KeyType, KeyState))
			{
				KeyValue->KeyEvent();
			}
		}
	}
	void KeyInput::AddKey(const Str::FString& _KeyName, Input::eKeyType _KeyType, Input::eButtonState _KeyState, std::function<void()> _KeyEvent)
	{
		auto Iter = KeyValues.find(_KeyName);
		if (Iter != KeyValues.end())
			return;

		KeyValue* KeyValue = new Game::KeyValue(_KeyType, _KeyState, _KeyEvent);
		KeyValues.insert(std::make_pair(_KeyName, KeyValue));
	}
}

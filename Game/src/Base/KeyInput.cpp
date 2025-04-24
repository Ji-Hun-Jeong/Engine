#include "pch.h"
#include "KeyInput.h"

namespace Game
{
	void KeyActioner::PerformKeyAction()
	{
		Str::FString KeyValue;
		while (!SelectedKeyValues.empty())
		{
			KeyValue = std::move(SelectedKeyValues.front());
			SelectedKeyValues.pop();

			Action(KeyValue);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

	void KeyInput::UpdateKeyState()
	{
		if (IsFocus == false)
			return;

		Input::eKeyType KeyType = Input::eKeyType::End;
		Input::eButtonState KeyState = Input::eButtonState::None;
		KeyStateValue Value = {};

		auto iter = ValueOfKey.begin();
		for (size_t i = 0; i < BeCheckedKeys.size(); ++i)
		{
			if (BeCheckedKeys[i] == false)
				continue;

			KeyType = Input::eKeyType(i);
			KeyState = Input::GetKeyState(KeyType);
			Value.KeyType = KeyType;
			Value.KeyState = KeyState;

			iter = ValueOfKey.find(Value.SolutionKey);

			if (iter != ValueOfKey.end())
				Actioner.SelectedKeyValues.push(iter->second);
		}
	}
	void KeyInput::AddKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState, const Str::FString& _KeyValue)
	{
		BeCheckedKeys[(size_t)_KeyType] = true;
		KeyStateValue Value = {};
		Value.KeyType = _KeyType;
		Value.KeyState = _KeyState;

		ValueOfKey.insert(std::make_pair(Value.SolutionKey, _KeyValue));
	}
}

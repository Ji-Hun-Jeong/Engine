#include "pch.h"
#include "KeyInput.h"

namespace Game
{
	void KeyActioner::PerformKeyAction()
	{
		KeyValue* KeyValue = nullptr;
		while (!SelectedKeyValues.empty())
		{
			KeyValue = SelectedKeyValues.front();
			SelectedKeyValues.pop();

			KeyValue->KeyEvent(KeyValue->KeyName);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

	KeyInput::~KeyInput()
	{
		for (auto iter = ValueOfKeys.begin(); iter != ValueOfKeys.end(); ++iter)
			delete iter->second;
	}

	void KeyInput::UpdateKeyState()
	{
		if (IsFocus == false)
			return;

		Input::eKeyType KeyType = Input::eKeyType::End;
		Input::eButtonState KeyState = Input::eButtonState::None;
		KeyStateValue Value = {};

		auto iter = ValueOfKeys.begin();
		for (size_t i = 0; i < BeCheckedKeys.size(); ++i)
		{
			if (BeCheckedKeys[i] == false)
				continue;

			KeyType = Input::eKeyType(i);
			KeyState = Input::GetKeyState(KeyType);
			Value.KeyType = KeyType;
			Value.KeyState = KeyState;

			iter = ValueOfKeys.find(Value.SolutionKey);

			if (iter != ValueOfKeys.end())
				Actioner.SelectedKeyValues.push(iter->second);
		}
	}
	void KeyInput::AddKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState, const Str::FString& _KeyName)
	{
		BeCheckedKeys[(size_t)_KeyType] = true;
		KeyStateValue Value = {};
		Value.KeyType = _KeyType;
		Value.KeyState = _KeyState;

		if (ValueOfKeys.find(Value.SolutionKey) != ValueOfKeys.end())
			return;

		KeyValue* KeyValue = new Game::KeyValue(_KeyName);

		ValueOfKeys.insert(std::make_pair(Value.SolutionKey, KeyValue));
	}
}

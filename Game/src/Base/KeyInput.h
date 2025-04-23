#pragma once
#include <Engine/src/Input/Input.h>

namespace Game
{
	union KeyStateValue
	{
		struct
		{
			Input::eKeyType KeyType;
			Input::eButtonState KeyState;
		};
		uint32_t SolutionKey;
	};

	class KeyActioner
	{
		friend class KeyInput;
	private:
		KeyActioner() = default;
		~KeyActioner() = default;

	public:
		void SetAction(std::function<void(const Str::FString&)> _Action) { Action = _Action; }
		void PerformKeyAction()
		{
			while (!SelectedKeyValues.empty())
			{
				Str::FString KeyValue = std::move(SelectedKeyValues.front());
				SelectedKeyValues.pop();

				Action(KeyValue);
			}
		}

	private:
		std::queue<Str::FString> SelectedKeyValues;
		std::function<void(const Str::FString&)> Action;
	};

	class KeyInput
	{
	public:
		KeyInput()
			: BeCheckedKeys{false}
			, IsFocus(true)
		{}
		~KeyInput() 
		{

		}

	public:
		void UpdateKeyState()
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

		KeyActioner* GetKeyActioner() { return &Actioner; }

		void AddKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState, const Str::FString& _KeyValue)
		{
			BeCheckedKeys[(size_t)_KeyType] = true;
			KeyStateValue Value = {};
			Value.KeyType = _KeyType;
			Value.KeyState = _KeyState;

			ValueOfKey.insert(std::make_pair(Value.SolutionKey, _KeyValue));
		}

		void SetFocus(bool _IsFocus) { IsFocus = _IsFocus; }
		
	private:
		std::array<bool, size_t(Input::eKeyType::End)> BeCheckedKeys;

		std::unordered_map<uint32_t, Str::FString> ValueOfKey;

		KeyActioner Actioner;

		bool IsFocus;
	};
}


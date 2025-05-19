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

	class KeyValue
	{
		friend class KeyActioner;
	public:
		KeyValue(const Str::FString& _KeyName)
			: KeyName(_KeyName)
		{}
		~KeyValue() = default;

	public:
		void SetKeyEvent(std::function<void(const Str::FString&)> _KeyEvent) { KeyEvent = _KeyEvent; }

	private:
		Str::FString KeyName;
		std::function<void(const Str::FString&)> KeyEvent;

	};

	class KeyActioner
	{
		friend class KeyInput;
	private:
		KeyActioner() = default;
		~KeyActioner() = default;

	public:
		void PerformKeyAction();

	private:
		std::queue<KeyValue*> SelectedKeyValues;

	};

	class KeyInput
	{
	public:
		KeyInput()
			: BeCheckedKeys{false}
			, IsFocus(true)
		{}
		KeyInput(const KeyInput&) = delete;
		~KeyInput();

	public:
		void UpdateKeyState();

		KeyActioner& GetKeyActioner() { return Actioner; }

		void AddKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState, const Str::FString& _KeyName);

		void SetFocus(bool _IsFocus) { IsFocus = _IsFocus; }

		KeyValue* GetKeyValue(Input::eKeyType _KeyType, Input::eButtonState _KeyState)
		{
			KeyStateValue Value = {};
			Value.KeyType = _KeyType;
			Value.KeyState = _KeyState;

			auto Iter = ValueOfKeys.find(Value.SolutionKey);
			if (Iter == ValueOfKeys.end())
				return nullptr;

			return Iter->second;
		}
		
	private:
		std::array<bool, size_t(Input::eKeyType::End)> BeCheckedKeys;

		// 그냥 쌩 배열로 해도될듯?
		std::unordered_map<uint32_t, KeyValue*> ValueOfKeys;

		KeyActioner Actioner;

		bool IsFocus;
	};
}


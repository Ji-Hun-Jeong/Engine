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
		void PerformKeyAction();

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
		~KeyInput() = default;

	public:
		void UpdateKeyState();

		KeyActioner* GetKeyActioner() { return &Actioner; }

		void AddKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState, const Str::FString& _KeyValue);

		void SetFocus(bool _IsFocus) { IsFocus = _IsFocus; }
		
	private:
		std::array<bool, size_t(Input::eKeyType::End)> BeCheckedKeys;

		// 그냥 쌩 배열로 해도될듯?
		std::unordered_map<uint32_t, Str::FString> ValueOfKey;

		KeyActioner Actioner;

		bool IsFocus;
	};
}


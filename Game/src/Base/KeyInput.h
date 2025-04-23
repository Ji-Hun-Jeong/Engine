#pragma once
#include <Engine/src/Input/Input.h>

namespace Game
{
	/*
		Input���� Key, State���� ��� ��ȯ
		KeyValues���� �� ���տ� ���� String�� ��ȯ
		�� String�� ���� Action����
	*/
	struct Key
	{
		Str::FString KeyName;
		Input::eButtonState KeyState = Input::eButtonState::None;
		std::function<void(const Str::FString&, Input::eButtonState)> KeyEvent = nullptr;
	};

	class KeyInput
	{
	public:
		KeyInput()
			: Keys{0}
			, IsFocus(true)
		{}
		~KeyInput() 
		{
			for (size_t i = 0; i < Keys.size(); ++i)
				if (Keys[i])
					delete Keys[i];
		}

	public:
		void UpdateKeyState()
		{
			if (IsFocus == false)
				return;

			for (size_t i = 0; i < Keys.size(); ++i)
			{
				if (Keys[i] == nullptr)
					continue;

				Input::eButtonState KeyState = Input::GetKeyState(Input::eKeyType(i));
				if (KeyState == Input::eButtonState::Hold
					|| KeyState == Input::eButtonState::Tap)
				{
					Keys[i]->KeyState = KeyState;

					PressedKeys.push(Keys[i]);
				}
			}
		}

		void PerformPressedKeys()
		{
			Key* Key = nullptr;
			while (PressedKeys.empty() == false)
			{
				Key = PressedKeys.front();
				PressedKeys.pop();
				Key->KeyEvent(Key->KeyName, Key->KeyState);
			}
		}

		void AddKey(Key* _KeyContext, Input::eKeyType _KeyType)
		{
			Keys[(size_t)_KeyType] = _KeyContext;
		}

		void SetFocus(bool _IsFocus) { IsFocus = _IsFocus; }
		
	private:
		std::array<Key*, size_t(Input::eKeyType::End)> Keys;

		std::queue<Key*> PressedKeys;

		bool IsFocus;
	};
}


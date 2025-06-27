#pragma once
#include <Engine/src/Time/Time.h>

namespace Game
{
	class TriggerVariable
	{
	public:
		TriggerVariable()
			: Trigger(false)
			, Timer(0.7f)
		{
		}
		~TriggerVariable() = default;

	public:
		void Tick()
		{
			Timer.GoOn();
			if (Timer.IsTimeOver())
			{
				// 약간의 텀을 둬서 행동전에 어떤 트리거를 발생시켜도 그 정도 시간은 이전행동이 끝난 후 발동할 수 있게
				Trigger = false;
				Timer.Reset();
				Timer.SetRun(false);
			}
		}
		void SetTrigger()
		{
			Trigger = true;
			Timer.Reset();
			Timer.SetRun(true);
		}
		bool IsTrigged() const { return Trigger; }

	private:
		Time::Timer Timer;
		bool Trigger;
	};

	class StateVariableTable
	{
	public:
		StateVariableTable() = default;
		~StateVariableTable() = default;

	public:
		void ResetTriggers()
		{
			for (auto& Iter : TriggerVariables)
				Iter.second.Tick();
		}

		int& RegistInt(const Str::FString& _VariableName, int _InitValue = 0)
		{
			auto Iter = IntVariables.insert(std::make_pair(_VariableName, _InitValue));

			return Iter.first->second;
		}
		float& RegistFloat(const Str::FString& _VariableName, float _InitValue = 0.0f)
		{
			auto Iter = FloatVariables.insert(std::make_pair(_VariableName, _InitValue));

			return Iter.first->second;
		}
		double& RegistDouble(const Str::FString& _VariableName, double _InitValue = 0.0f)
		{
			auto Iter = DoubleVariables.insert(std::make_pair(_VariableName, _InitValue));

			return Iter.first->second;
		}
		bool& RegistBool(const Str::FString& _VariableName, bool _InitValue = false)
		{
			auto Iter = BoolVariables.insert(std::make_pair(_VariableName, _InitValue));

			return Iter.first->second;
		}
		TriggerVariable& RegistTrigger(const Str::FString& _VariableName)
		{
			auto Iter = TriggerVariables.insert(std::make_pair(_VariableName, TriggerVariable()));

			return Iter.first->second;
		}

		int& GetInt(const Str::FString& _VariableName)
		{
			auto Iter = IntVariables.find(_VariableName);

			return Iter->second;
		}
		float& GetFloat(const Str::FString& _VariableName)
		{
			auto Iter = FloatVariables.find(_VariableName);

			return Iter->second;
		}
		double& GetDouble(const Str::FString& _VariableName)
		{
			auto Iter = DoubleVariables.find(_VariableName);

			return Iter->second;
		}
		bool& GetBool(const Str::FString& _VariableName)
		{
			auto Iter = BoolVariables.find(_VariableName);

			return Iter->second;
		}
		TriggerVariable& GetTrigger(const Str::FString& _VariableName)
		{
			auto Iter = TriggerVariables.find(_VariableName);

			return Iter->second;
		}

	private:
		std::map<Str::FString, int> IntVariables;
		std::map<Str::FString, float> FloatVariables;
		std::map<Str::FString, double> DoubleVariables;
		std::map<Str::FString, bool> BoolVariables;
		std::map<Str::FString, TriggerVariable> TriggerVariables;

	};
}

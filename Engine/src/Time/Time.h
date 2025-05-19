#pragma once

namespace Time
{
	extern float GetDT();
	extern void Init();
	extern void Update();

	class Timer
	{
	public:
		Timer(float _SettingTime, bool* _BoolValue)
			: SettingTime(_SettingTime), RemainTime(0.0f)
			, BoolValue(_BoolValue)
			, Run(false)
		{
		}
		~Timer() = default;

	public:
		void GoOn()
		{
			if (Run == false)
				return;

			RemainTime -= GetDT();
			if (RemainTime <= 0.0f)
				*BoolValue = true;
		}

		void Reset()
		{
			RemainTime = SettingTime;
			*BoolValue = false;
		}

		void SetRun(bool _Run) { Run = _Run; }

	private:
		float SettingTime;
		float RemainTime;

		bool* BoolValue;

		bool Run;
	};

	extern void RegistTimer(Timer* _Timer);
	extern void DetachTimer(Timer* _Timer);
};
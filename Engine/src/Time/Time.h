#pragma once

namespace Time
{
	extern float GetDT();
	extern void Init();
	extern void Update();

	class Timer
	{
	public:
		Timer(float _SettingTime)
			: SettingTime(_SettingTime), RemainTime(_SettingTime)
			, TimeOver(false)
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
				TimeOver = true;
		}

		void Reset()
		{
			RemainTime = SettingTime;
			TimeOver = false;
		}

		void SetRun(bool _Run) { Run = _Run; }
		bool IsTimeOver() const { return TimeOver; }

	private:
		float SettingTime;
		float RemainTime;

		bool TimeOver;

		bool Run;
	};
};
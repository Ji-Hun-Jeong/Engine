#pragma once
#include "GraphicsTime.h"

namespace Graphics
{
	class StateCondition
	{
	public:
		virtual ~StateCondition() = default;
		virtual bool Satisfy() = 0;

	protected:

	};

	class IntCondition : public StateCondition
	{
	public:
		IntCondition(int* _Value, int _Threshold, bool _Less)
			: Value(_Value), Threshold(_Threshold), Less(_Less)
		{
		}
		~IntCondition() {}

	public:
		bool Satisfy() override
		{
			if (Less)
				return *Value < Threshold;
			else
				return *Value > Threshold;
		}

	private:
		int* Value;
		int Threshold;
		bool Less;
	};

	class FloatCondition : public StateCondition
	{
	public:
		FloatCondition(float* _Value, float _Threshold, bool _Less)
			: Value(_Value), Threshold(_Threshold), Less(_Less)
		{
		}
		~FloatCondition() {}

	public:
		bool Satisfy() override
		{
			if (Less)
				return *Value < Threshold;
			else
				return *Value > Threshold;
		}

	private:
		float* Value;
		float Threshold;
		bool Less;
	};

	class BoolCondition : public StateCondition
	{
	public:
		BoolCondition(bool* _Value, bool _Expected)
			: Value(_Value), Expected(_Expected)
		{
		}
		~BoolCondition() {}

	public:
		bool Satisfy() override
		{
			return *Value == Expected;
		}

	private:
		bool* Value;
		bool Expected;

	};

	class RENDERER_API TriggerVariable
	{
	public:
		TriggerVariable()
			: Trigger(false)
			, Timer(0.7f)
		{}
		~TriggerVariable() = default;

	public:
		void Tick()
		{
			Timer.GoOn();
			if(Timer.IsTimeOver())
			{
				// �ణ�� ���� �ּ� �ൿ���� � Ʈ���Ÿ� �߻����ѵ� �� ���� �ð��� �����ൿ�� ���� �� �ߵ��� �� �ְ�
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
		GraphicsTime::Timer Timer;
		bool Trigger;
	};

	class TriggerCondition : public StateCondition
	{
	public:
		TriggerCondition(TriggerVariable& _Trigger)
			: Trigger(_Trigger)
		{
		}
		~TriggerCondition() {}

	public:
		bool Satisfy() override
		{
			return Trigger.IsTrigged();
		}

	private:
		TriggerVariable& Trigger;

	};

}
#pragma once

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
}
#pragma once

namespace Game
{
	class State
	{
	public:
		explicit State(const std::string& _StateName)
			: StateName(_StateName)
		{
			
		}
		State(const State&) = delete;
		virtual ~State() {}

	public:
		virtual void EnterState() = 0;
		virtual void OnState() = 0;
		virtual void ExitState() = 0;

	protected:
		std::string StateName;
		std::function<void()> MoveFunction;
		// 이동
		// 액션리스트 정도?

	};

	class StateController
	{
	public:
		explicit StateController() {}
		StateController(const StateController&) = delete;
		~StateController() {}

	public:
		void RunState()
		{
			CurrentState->OnState();
		}
		State* GetCurrentState() const { return CurrentState; }


	private:
		std::unordered_map<std::string, State*> States;

		State* CurrentState;
	};
}
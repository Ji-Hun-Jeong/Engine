#pragma once

namespace Game
{
	class State
	{
	public:
		explicit State(const std::string& _StateName)
			: StateName(_StateName)
		{}
		virtual ~State() = 0 {}

	public:
		virtual void EnterState() = 0;
		virtual void OnState() = 0;
		virtual void ExitState() = 0;

		const std::string& GetName() const { return StateName; }

	protected:
		std::string StateName;
		std::function<void()> MoveFunction;

	};

	class StateController
	{
	public:
		explicit StateController()
			: CurrentState(nullptr) 
		{
		}
		StateController(const StateController&) = delete;
		~StateController() {}

	public:
		void RunState()
		{
			CurrentState->OnState();
		}
		State* GetCurrentState() const { return CurrentState; }
		void AddState(State* _State) { States.insert(std::make_pair(_State->GetName(), _State)); }

	private:
		std::unordered_map<std::string, State*> States;

		State* CurrentState;
	};
}
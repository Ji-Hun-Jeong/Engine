#pragma once

namespace Game
{
	class State
	{
	public:
		explicit State(const Str::FString& _StateName)
			: StateName(_StateName)
		{}
		virtual ~State() = 0 {}

	public:
		virtual void EnterState() = 0;
		virtual void OnState() = 0;
		virtual void ExitState() = 0;

		const Str::FString& GetName() const { return StateName; }

	protected:
		Str::FString StateName;
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
		std::unordered_map<Str::FString, State*> States;

		State* CurrentState;
	};
}
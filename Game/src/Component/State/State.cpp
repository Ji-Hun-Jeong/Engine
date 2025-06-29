#include "pch.h"
#include "State.h"
#include "Component/Animation/Animator.h"

namespace Game
{
    State::~State()
    {
        if (StateAnimation)
            delete StateAnimation;
        for (auto Transition : Transitions)
            delete Transition;
    }
    void State::EnterState()
    {
        if (EnterStateFunc)
            EnterStateFunc();
    }

    void State::ExitState()
    {
        if (ExitStateFunc)
            ExitStateFunc();
    }

    void StateMachine::DecideUpdateWhether(Animator& _Animator)
    {
        UpdateWhether = _Animator.CurrentAnimationSkip();
    }

    void StateMachine::SetBaseAnimation(Animator& _Animator)
    {
        if (StateChanged == false)
            return;

        Animation* StateAnimation = CurrentState->GetStateAnimation();

        if (StateAnimation)
            _Animator.SetCurrentAnimation(StateAnimation);

        StateChanged = false;
    }

}
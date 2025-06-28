#include "pch.h"
#include "State.h"
#include "Component/Animation/Animator.h"

namespace Game
{
    State::~State()
    {
        if (BaseAnimation)
            delete BaseAnimation;
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

    void StateMachine::SetBaseAnimation(Animator& _Animator)
    {
        Animation* BaseAnimation = CurrentState->GetBaseAnimation();

        if (BaseAnimation)
            _Animator.ReserveNextAnimation(EAnimationPriority::Base, BaseAnimation);
    }

    void AddTransition(StateMachine& _StateMachine, StateCondition* _Condition, State* _TailState, State* _HeadState, bool _ForceExit)
    {
        StateTransition* Transition = new StateTransition(_Condition, _HeadState);
        Transition->SetForceExit(_ForceExit);
        _StateMachine.AddTransition(_TailState, Transition);
    }

}
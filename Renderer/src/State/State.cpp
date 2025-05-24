#include "pch.h"
#include "State.h"
#include "Animation/Animation.h"

namespace Graphics
{
    void State::Update(RenderInterface& _RenderInterface)
    {
        if (Anim)
        {
            Anim->Update(_RenderInterface);
        }
    }

    void State::ExitState()
    {
        if (Anim)
        {
            Anim->ResetAnimation();
        }
    }

    void AddTransition(StateMachine& _StateMachine, StateCondition* _Condition, State& _TailState, State& _HeadState)
    {
        Graphics::StateTransition* Transition = new Graphics::StateTransition(_Condition, _HeadState);
        _StateMachine.AddTransition(&_TailState, Transition);
    }
}
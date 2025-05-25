#include "pch.h"
#include "State.h"
#include "Animation/Animation.h"

namespace Graphics
{
    void State::Update(IRenderInterface& _RenderInterface)
    {
        if (Anim)
            Anim->Update(_RenderInterface);
        
    }

    void State::EnterState()
    {
        if (EnterStateFunc)
            EnterStateFunc();
    }

    void State::ExitState()
    {
        if (Anim)
            Anim->ResetAnimation();
        if (ExitStateFunc)
            ExitStateFunc();
    }

    bool State::IsFinish()
    {
        if (Anim)
        {
            return Anim->IsFinish();
        }
        return true;
    }

    void AddTransition(StateMachine& _StateMachine, StateCondition* _Condition, State* _TailState, State* _HeadState, bool _ForceExit)
    {
        Graphics::StateTransition* Transition = new Graphics::StateTransition(_Condition, *_HeadState);
        Transition->SetForceExit(_ForceExit);
        _StateMachine.AddTransition(_TailState, Transition);
    }
}
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
}
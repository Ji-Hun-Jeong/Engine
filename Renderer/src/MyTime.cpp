#include "pch.h"
#include "MyTime.h"

namespace GraphicsTime
{
    float DT = 0.0f;

    float GraphicsTime::GetDT()
    {
        return DT;
    }

    void GraphicsTime::SetDT(float _DT)
    {
        DT = _DT;
    }
}


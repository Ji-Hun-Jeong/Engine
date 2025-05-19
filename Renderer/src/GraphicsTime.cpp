#include "pch.h"
#include "GraphicsTime.h"

namespace GraphicsTime
{
    float DT = 0.0f;

    void GraphicsTime::Update(float _DT)
    {
        DT = _DT;
    }

    float GraphicsTime::GetDT()
    {
        return DT;
    }
}


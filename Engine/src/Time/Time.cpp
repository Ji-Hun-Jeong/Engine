#include "pch.h"
#include "Time.h"

namespace Time 
{
    std::vector<Timer*> Timers;

    LARGE_INTEGER Frequency;     
    LARGE_INTEGER PrevTime;      
    LARGE_INTEGER CurrentTime;   
    float DeltaTime;

    float GetDT() { return DeltaTime; }

    void Init() 
    {
        QueryPerformanceFrequency(&Frequency); 
        QueryPerformanceCounter(&PrevTime);    
        CurrentTime = PrevTime;                
        DeltaTime = 0.0;                       
    }

    void Update() 
    {
        QueryPerformanceCounter(&CurrentTime); 

        DeltaTime = static_cast<float>(CurrentTime.QuadPart - PrevTime.QuadPart) / static_cast<float>(Frequency.QuadPart);
        PrevTime = CurrentTime;

        if (1 / 30.0f < DeltaTime)
            DeltaTime = 1 / 60.0f;

    }
}


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

        for (auto& Timer : Timers)
            Timer->GoOn();
    }


    void RegistTimer(Timer* _Timer)
    {
        Timers.push_back(_Timer);
    }
    void DetachTimer(Timer* _Timer)
    {
        for (auto Iter = Timers.begin(); Iter != Timers.end(); )
        {
            if (_Timer == *Iter)
            {
                delete* Iter;
                Iter = Timers.erase(Iter);
            }
            else
                ++Iter;
        }
    }
}


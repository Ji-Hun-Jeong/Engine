#include "pch.h"
#include "Time.h"

namespace Time 
{
    LARGE_INTEGER Frequency;     
    LARGE_INTEGER PrevTime;      
    LARGE_INTEGER CurrentTime;   
    float DeltaTime;

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
    }
}


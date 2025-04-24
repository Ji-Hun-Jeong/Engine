#include "pch.h"
#include "Time.h"

namespace Time 
{
    LARGE_INTEGER Frequency;     
    LARGE_INTEGER PrevTime;      
    LARGE_INTEGER CurrentTime;   
    float DeltaTime;

    inline float GetDT() { return DeltaTime; }

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
        /*static int frame = 0;
        static float sum = 0.0f;
        sum += DeltaTime;
        frame += 1;
        if (sum >= 1.0f)
        {
            std::cout << frame << '\n';
            sum = 0.0f;
            frame = 0;
        }*/
        PrevTime = CurrentTime;
    }
}


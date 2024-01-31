#include "EngineTime.h"
#include <Windows.h>

UEngineTime::UEngineTime() 
{
	TimeCheckStart();
}

UEngineTime::~UEngineTime() 
{
}


void UEngineTime::TimeCheckStart()
{
	QueryPerformanceFrequency(&Count);  // 1초간의 진동수
	QueryPerformanceCounter(&PrevTime); // 현재까지의 진동수

	dCount = static_cast<double>(Count.QuadPart);
}

float UEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);

	// 정밀도를 높이기 위해서 double로 계산한다.
	double dTick = static_cast<double>(Tick);
	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	return static_cast<float>(DeltaTime);
}
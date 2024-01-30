#include "EngineTime.h"
#include <Windows.h>

EngineTime::EngineTime() 
{
	TimeCheckStart();
}

EngineTime::~EngineTime() 
{
}


void EngineTime::TimeCheckStart()
{
	QueryPerformanceFrequency(&Count);  // 1�ʰ��� ������
	QueryPerformanceCounter(&PrevTime); // ��������� ������

	dCount = static_cast<double>(Count.QuadPart);
}

float EngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);

	// ���е��� ���̱� ���ؼ� double�� ����Ѵ�.
	double dTick = static_cast<double>(Tick);
	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	return static_cast<float>(DeltaTime);
}
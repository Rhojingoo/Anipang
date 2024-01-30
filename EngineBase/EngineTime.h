#pragma once
#include <Windows.h>

class EngineTime
{
public:
	EngineTime();
	~EngineTime();

	EngineTime(const EngineTime& _Other)						= delete;
	EngineTime(EngineTime&& _Other) noexcept					= delete;
	EngineTime& operator=(const EngineTime& _Other)				= delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept			= delete;

	void TimeCheckStart();

	float TimeCheck();

	double GetDeltaTime()
	{
		return DeltaTime;
	}

protected:

private:
	LARGE_INTEGER Count;
	LARGE_INTEGER PrevTime;
	LARGE_INTEGER CurTime;
	double dCount;
	double DeltaTime;
};


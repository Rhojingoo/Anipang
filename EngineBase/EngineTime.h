#pragma once
#include <Windows.h>

class UEngineTime
{
public:
	UEngineTime();
	~UEngineTime();

	UEngineTime(const UEngineTime& _Other)						= delete;
	UEngineTime(UEngineTime&& _Other) noexcept					= delete;
	UEngineTime& operator=(const UEngineTime& _Other)				= delete;
	UEngineTime& operator=(UEngineTime&& _Other) noexcept			= delete;

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


#pragma once
#include <EngineCore\Actor.h>

class ANumber;
class ATime_Gauge : public AActor
{
public : 
	ATime_Gauge();
	~ATime_Gauge();

	ATime_Gauge(const ATime_Gauge& _Other)					 = delete;
	ATime_Gauge(ATime_Gauge& _Other) noexcept					 = delete;
	ATime_Gauge& operator =(const ATime_Gauge& _Other)		 = delete;
	ATime_Gauge& operator =(ATime_Gauge& _Other) noexcept		 = delete;

	void TimerStart() { Start = true; }
	bool IsFinish() { return Finish; }

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool Start						= false;
	bool Finish						= false;
	bool NumCreate					= false;
	bool Hurry						= false;

	float Size						= 458.f;
	float TotalSize					= 458.f;
	float TotalTime					= 60.f;
	float Time						= TotalTime;
	float PreveTime					= TotalTime;
		
	ANumber* Tens = nullptr;
	ANumber* Units = nullptr;
};


#pragma once
#include <EngineCore\Actor.h>

class ATimer : public AActor
{
public : 
	ATimer();
	~ATimer();

	ATimer(const ATimer& _Other)					 = delete;
	ATimer(ATimer& _Other) noexcept					 = delete;
	ATimer& operator =(const ATimer& _Other)		 = delete;
	ATimer& operator =(ATimer& _Other) noexcept		 = delete;

	void TimerStart() { Time = true; }
	bool IsFinish() { return Finish; }

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool Start						= false;
	bool Finish						= false;
	float Size						= 458.f;
	float TotalSize					= 458.f;
	float TotalTime					= 5.f;
	float Time						= TotalTime;
	float PreveTime					= TotalTime;


};


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

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool Start			= false;
	float Time			= 10.f;
	int	  Size			= 458;
	int	intTime = 0;
	int mSize = 0;
};


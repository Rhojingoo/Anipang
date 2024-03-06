#pragma once
#include <EngineCore\Actor.h>

class ANumber;
class ATime_Gauge : public AActor
{
public : 
	ATime_Gauge();
	~ATime_Gauge();

	ATime_Gauge(const ATime_Gauge& _Other)						 = delete;
	ATime_Gauge(ATime_Gauge& _Other) noexcept					 = delete;
	ATime_Gauge& operator =(const ATime_Gauge& _Other)			 = delete;
	ATime_Gauge& operator =(ATime_Gauge& _Other) noexcept		 = delete;

	void TimerStart() { Start = true; }
	bool IsFinish() { return Finish; }
	void Finishreturn()
	{
		Size = TotalSize;
		PreveTime = TotalTime;
		Time = TotalTime;
		Finish = false;
		Start = false;
		Hurry = false;
		Renderer->SetScale({Size, 30.f});//231,705
		SetActorLocation({ 231,705 });
		Renderer->ChangeAnimation("Nomarl");
	}

	void Test_BlockMove_Mode_On() { Test_BlockMove_Mode = true; }
	void Test_BlockMove_Mode_Off() { Test_BlockMove_Mode = false; }
	void TimeStopOn() { TimeStop = true; }
	void TimeStopOff() { TimeStop = false; }


protected:
	UImageRenderer* Renderer		= nullptr;
	FVector Pos						= {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool Start						= false;
	bool Finish						= false;
	bool NumCreate					= false;
	bool Hurry						= false;

	float Size						= 458.f;
	float TotalSize					= 458.f;
	float TotalTime					= 10.f;
	float Time						= TotalTime;
	float PreveTime					= TotalTime;
		
	ANumber* Tens					= nullptr;
	ANumber* Units					= nullptr;

	bool Test_BlockMove_Mode		= false;
	bool TimeStop					= false;
};


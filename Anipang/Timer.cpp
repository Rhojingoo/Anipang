#include "Timer.h"

ATimer::ATimer()
{
}

ATimer::~ATimer()
{
}

void ATimer::BeginPlay()
{
	Renderer = CreateImageRenderer(5);
	Renderer->SetImage("UnderBarUI2.png");
	Renderer->SetTransform({ {0.f,0.f}, {Size, 30.f} });
	Renderer->SetImageCuttingTransform({ {0,0}, {410, 29} });
}

void ATimer::Tick(float _DeltaTime)
{
	Pos = GetActorLocation();
	Time -= _DeltaTime;
	float checktime =  PreveTime - Time;
	if (checktime >= 1.f)
	{
		PreveTime = Time;
		float SumTotalSize = (TotalSize - (TotalSize * (Time / TotalTime))) ;
		float SumChangeSize = (Size - (TotalSize * (Time / TotalTime)));
		Size = TotalSize - SumTotalSize;
		Renderer->SetScale({ Size, 30.f });
		Pos.X = Pos.X - SumChangeSize/2;
		SetActorLocation(Pos);
	}

	if (Time <= 0.f)
	{
		Finish = true;
	}
}

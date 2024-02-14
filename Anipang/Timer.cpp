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
	Renderer->SetTransform({ {0,0}, {Size, 30} });
	Renderer->SetImageCuttingTransform({ {0,0}, {418, 29} });

	intTime = static_cast<int>(Time);
	mSize = Size / intTime;
}

void ATimer::Tick(float _DeltaTime)
{
	Time -= 1.f * _DeltaTime;
	intTime = static_cast<int>(Time);
	int CheckSize = mSize + (mSize * (intTime/10));
	Size = CheckSize * 10;
	Renderer->SetTransform({ {0,0}, {Size, 30} });

	if (Time <= 0.f)
	{
		int a = 0;
	}
}

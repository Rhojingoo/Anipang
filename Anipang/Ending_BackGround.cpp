#include "Ending_BackGround.h"

AEnding_BackGround::AEnding_BackGround()
{
}

AEnding_BackGround::~AEnding_BackGround()
{
}

void AEnding_BackGround::BeginPlay()
{
	AActor::BeginPlay();
	{
		// 타이틀 배경
		Renderer = CreateImageRenderer(0);
		Renderer->SetImage("Ending_Level.png");
		SetActorLocation({ 240, 370 });
		Renderer->SetTransform({ {0,0}, {480, 780} });
		Renderer->SetImageCuttingTransform({ {0,0}, {1399, 812} });
	}
}

void AEnding_BackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

#include "Play_Frame.h"

APlay_Frame::APlay_Frame()
{
}

APlay_Frame::~APlay_Frame()
{
}

void APlay_Frame::BeginPlay()
{
	AActor::BeginPlay();
	{
		// 타이틀 배경
		Renderer = CreateImageRenderer(0);
		Renderer->SetImage("PlayFrame.bmp");
		SetActorLocation({ 240, 400 });
		Renderer->SetTransform({ {0,0}, {480, 800} });
		Renderer->SetImageCuttingTransform({ {0,0}, {367, 609} });
	}
}

void APlay_Frame::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

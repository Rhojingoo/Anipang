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
		// Ÿ��Ʋ ���
		Renderer = CreateImageRenderer(0);
		Renderer->SetImage("PlayFrame.bmp");
		SetActorLocation({ 240, 400 });
		Renderer->SetTransform({ {0,0}, {480, 800} });
		Renderer->SetImageCuttingTransform({ {0,0}, {367, 609} });
	}

	{
		// ��������Ʈ �׽�Ʈ�̹���
		UImageRenderer* Renderer2 = CreateImageRenderer(1);
		Renderer2->SetImage("Rabbit");
		Renderer2->SetTransform({ {100,200}, {133, 139} });
		Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		Renderer2->CreateAnimation("Idle", "Rabbit", 0, 2, 1.1f, true);
		Renderer2->ChangeAnimation("Idle");
	}

}

void APlay_Frame::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

#include "Title_LogoChick.h"

ATitle_LogoChick::ATitle_LogoChick()
{
}

ATitle_LogoChick::~ATitle_LogoChick()
{
}

void ATitle_LogoChick::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer2 = CreateImageRenderer(5);
	Renderer2->SetImage("Intro_Chick");
	SetActorLocation({ 330, 100 });
	Renderer2->SetTransform({ {20,100}, {155, 160} });
	Renderer2->SetImageCuttingTransform({ {0,0}, {155, 160} });
	Renderer2->CreateAnimation("Idle", "Intro_Chick", 0, 7, 0.1f, true);
	Renderer2->ChangeAnimation("Idle");
}

void ATitle_LogoChick::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

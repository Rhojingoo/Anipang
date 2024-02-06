#include "Title_PointAnimation.h"

ATitle_PointAnimation::ATitle_PointAnimation()
{
}

ATitle_PointAnimation::~ATitle_PointAnimation()
{
}

void ATitle_PointAnimation::BeginPlay()
{
	AActor::BeginPlay();
	UImageRenderer* Renderer2 = CreateImageRenderer(1);
	Renderer2->SetImage("Intro_OBJ");
	SetActorLocation({ 240, 525 });
	Renderer2->SetTransform({ {20,100}, {100, 105} });
	Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer2->CreateAnimation("Idle", "Intro_OBJ", 0, 1, 0.1f, true);
	Renderer2->ChangeAnimation("Idle");
}

void ATitle_PointAnimation::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}



#include "Title_Button.h"

ATitle_Button::ATitle_Button()
{
}

ATitle_Button::~ATitle_Button()
{
}

void ATitle_Button::BeginPlay()
{
	AActor::BeginPlay();
	UImageRenderer* Renderer2 = CreateImageRenderer(1);
	Renderer2->SetImage("Intro_OBJ");	
	SetActorLocation({ 240, 400 });
	Renderer2->SetTransform({ {20,100}, {100, 105} });
	Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer2->CreateAnimation("Idle", "Intro_OBJ", 0, 1, 0.1f, true);
	Renderer2->ChangeAnimation("Idle");
}

void ATitle_Button::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

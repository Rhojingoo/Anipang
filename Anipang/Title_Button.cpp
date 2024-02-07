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

	Renderer = CreateImageRenderer(6);
	Renderer->SetImage("GameStart_UI.png");
	SetActorLocation({ 200, 475 });
	Renderer->SetTransform({ {50,50}, {250, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {350, 120} });
}

void ATitle_Button::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();
}

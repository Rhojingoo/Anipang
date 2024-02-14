#include "Game_Start.h"

AGame_Start::AGame_Start()
{
}

AGame_Start::~AGame_Start()
{
}

void AGame_Start::BeginPlay()
{
	Renderer = CreateImageRenderer(500);
	Renderer->SetImage("GameStart");
	Renderer->SetTransform({ {0,0}, {177, 260} });
	Renderer->SetImageCuttingTransform({ {0,0}, {177, 260} });
	Renderer->CreateAnimation("Idle", "GameStart", 0, 11, 0.1f, false);
	Renderer->ChangeAnimation("Idle");
}
//
void AGame_Start::Tick(float _DeltaTime)
{
	if (Start == true)
	{
		Destroy(0.f);
	}


	if (Renderer->IsCurAnimationEnd() == true)
	{
		Start = true;
	}
}

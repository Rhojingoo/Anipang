#include "Game_End.h"

AGame_End::AGame_End()
{
}

AGame_End::~AGame_End()
{
}

void AGame_End::BeginPlay()
{
	Renderer = CreateImageRenderer(5);
	Renderer->SetImage("GameEnd");
	Renderer->SetTransform({ {0,0}, {236, 472} });
	Renderer->SetImageCuttingTransform({ {0,0}, {236, 472} });
	Renderer->CreateAnimation("Idle", "GameEnd", 0, 9, 0.1f, true);
	Renderer->ChangeAnimation("Idle");
}
//			
void AGame_End::Tick(float _DeltaTime)
{
	//if (Renderer->IsCurAnimationEnd() == true)
	//{
	//	Destroy(0.f);
	//}
}

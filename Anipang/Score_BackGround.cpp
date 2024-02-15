#include "Score_BackGround.h"
#

AScore_BackGround::AScore_BackGround()
{
}

AScore_BackGround::~AScore_BackGround()
{
}

void AScore_BackGround::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(0);
	Renderer->SetImage("Score_BG.png");
	SetActorLocation({ 240, 400 });
	Renderer->SetTransform({ {0,0}, {480, 800} });
	
}

void AScore_BackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

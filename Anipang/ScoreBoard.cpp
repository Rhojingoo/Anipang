#include "ScoreBoard.h"


AScoreBoard::AScoreBoard()
{
}

AScoreBoard::~AScoreBoard()
{
}

void AScoreBoard::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("ScoreBoard.png");
	SetActorLocation({ 240, 400 });
	Renderer->SetTransform({ {0,0}, {412, 686} });
}

void AScoreBoard::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

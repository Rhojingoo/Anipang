#include "Screen_Score_Board.h"

AScreen_Score_Board::AScreen_Score_Board()
{
}

AScreen_Score_Board::~AScreen_Score_Board()
{
}

void AScreen_Score_Board::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(0);
	Renderer->SetImage("ScreenScoreBoard.png");
	Renderer->SetTransform({ {0,0}, {345, 520} });
}

void AScreen_Score_Board::Tick(float _DeltaTime)
{
	AActor::Tick( _DeltaTime);
}

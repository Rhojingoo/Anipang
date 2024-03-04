#include "RecordBoard.h"

ARecordBoard::ARecordBoard()
{
}

ARecordBoard::~ARecordBoard()
{
}

void ARecordBoard::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(5);
	Renderer->SetImage("RecordBoard.png");
	SetActorLocation({ 235, 280 });
	Renderer->SetTransform({ {0,0}, {450, 475} });
}

void ARecordBoard::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

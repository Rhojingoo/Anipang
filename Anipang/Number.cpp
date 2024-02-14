#include "Number.h"

ANumber::ANumber()
{
}

ANumber::~ANumber()
{
}

void ANumber::BeginPlay()
{
	AActor::BeginPlay();
	//Renderer = CreateImageRenderer(20);
	//Renderer->SetImage("Big_Number");
	//Renderer->SetTransform({ {0,0}, {128, 128} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {128, 128} });
	//Renderer->CreateAnimation("Idle", "Big_Number", 0, 13, 0.1f, true);
	//Renderer->ChangeAnimation("Idle");


	Renderer = CreateImageRenderer(20);
	Renderer->SetImage("Small_Number");
	Renderer->SetTransform({ {0,0}, {64, 64} });
	Renderer->SetImageCuttingTransform({ {0,0}, {64, 64} });
	Renderer->CreateAnimation("Idle", "Small_Number", 0, 13, 0.1f, true);
	Renderer->ChangeAnimation("Idle");
}

void ANumber::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

#include "Manual.h"

AManual::AManual()
{
}

AManual::~AManual()
{
}

void AManual::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(101);
	Renderer->SetImage("manual.png");
	Renderer->SetTransform({ {0,0}, {480, 363} });
}

void AManual::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

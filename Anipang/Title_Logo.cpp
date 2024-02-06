#include "Title_Logo.h"

ATitle_Logo::ATitle_Logo()
{
}

ATitle_Logo::~ATitle_Logo()
{
}

void ATitle_Logo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer(2);
	Renderer->SetImage("Intro_Logo4.png");
	SetActorLocation({ 240, 400 });
	Renderer->SetTransform({ {10,-185}, {450, 400} });
	Renderer->SetImageCuttingTransform({ {0,0}, {750, 750} });
}

void ATitle_Logo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

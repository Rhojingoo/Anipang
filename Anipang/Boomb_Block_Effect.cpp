#include "Boomb_Block_Effect.h"

ABoomb_Block_Effect::ABoomb_Block_Effect()
{
}

ABoomb_Block_Effect::~ABoomb_Block_Effect()
{
}

void ABoomb_Block_Effect::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(10);
	Renderer->SetImage("Phoenix Landing");
	Renderer->SetTransform({ {100,200}, {75, 200} });
	Renderer->SetImageCuttingTransform({ {0,0}, {70, 250} });
	Renderer->CreateAnimation("Idle", "Phoenix Landing", 0, 6, 0.1f, true);
	Renderer->ChangeAnimation("Idle");
}

void ABoomb_Block_Effect::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (Renderer->IsCurAnimationEnd() == true)
	{
		Destroycheck += 1;
	}

	if (Destroycheck >= 5)
	{
		int a = 0;
		Destroy(0.f);
	}
}

#include "BlockBoomb_Effect.h"

ABlockBoomb_Effect::ABlockBoomb_Effect()
{
}

ABlockBoomb_Effect::~ABlockBoomb_Effect()
{
}

void ABlockBoomb_Effect::BeginPlay()
{
	Renderer = CreateImageRenderer(5);
	Renderer->SetImage("Block_Effect");	
	Renderer->SetTransform({ {0,0}, {133, 139} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Block_Effect", 0, 4, 0.1f, false);
	Renderer->ChangeAnimation("Idle");
}

void ABlockBoomb_Effect::Tick(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		Destroy(0.f);
	}
}

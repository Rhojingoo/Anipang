#include "BoombBlock_Effect.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

ABoombBlock_Effect::ABoombBlock_Effect()
{
}

ABoombBlock_Effect::~ABoombBlock_Effect()
{
}

void ABoombBlock_Effect::BeginPlay()
{
	#pragma region 테스트 코드
	{
		AActor::BeginPlay();
		Renderer = CreateImageRenderer(20);	
		Renderer->SetImage("Boomb_Effect");
		Renderer->SetTransform({ {0,-175}, {135, 350} });
		Renderer->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
		Renderer->ChangeAnimation("Idle");

	}
		/*Destroy(2.0f);*/
	#pragma endregion
}

void ABoombBlock_Effect::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (SideRender == true)
	{
		Renderer->SetTransform({ {0,-125}, {135, 350} });
		SideRender = false;
		DeathTimeStart = true;
	}
	if (DeathTimeStart == true)
	{
		DeathTimeCheck -= _DeltaTime;

		if (DeathTimeCheck <= 0.f)
		{
			DeathTimeStart = false;
			Death = true;
		}
	}

	AddActorLocation(Dir * Speed * _DeltaTime);	
}


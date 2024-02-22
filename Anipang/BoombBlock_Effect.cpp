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

	AActor::BeginPlay();
	//{
	//	DirRenderer = CreateImageRenderer(20);
	//	DirRenderer->SetImage("Boomb_Effect_Dir");
	//	DirRenderer->SetTransform({ {0,-175}, {135, 350} });
	//	DirRenderer->CreateAnimation("Idle", "Boomb_Effect_Dir", 0, 6, 0.1f, true);
	//	DirRenderer->ChangeAnimation("Idle");
	//	//DirRenderer->SetTransform({ {0,0}, FVector{51, 93} *3 });
	//}
	//{
	//	
	//	Renderer = CreateImageRenderer(20);
	//	Renderer->SetImage("Boomb_Effect");
	//	Renderer->SetTransform({ {0,-175}, {135, 350} });
	//	Renderer->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
	//	Renderer->ChangeAnimation("Idle");
	//}

	{
		DirRenderer = CreateImageRenderer(20);
		DirRenderer->SetImage("Boomb_Effect");
		DirRenderer->SetTransform({ {0,-175}, {135, 350} });
		DirRenderer->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
		DirRenderer->ChangeAnimation("Idle");
	}



		/*Destroy(2.0f);*/
	#pragma endregion
}

void ABoombBlock_Effect::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


	static float Angle = 0.0f;
	Angle += _DeltaTime * 360.0f;
	//float4 Dir = float4::DegToDir(Angle);

	DirRenderer->SetAngle(Angle);

	//FVector Dir = { 100.0f, -100.0f };

	//Dir.RotationZToDeg(-45.0f);

	////static float Angle = 0.0f;
	////Angle += _DeltaTime * 360.0f;

	//Renderer->SetPosition(Dir);






	//if (SideRender == true)
	//{
	//	Renderer->SetTransform({ {0,-125}, {135, 350} });
	//	SideRender = false;
	//	DeathTimeStart = true;
	//}
	//if (DeathTimeStart == true)
	//{
	//	DeathTimeCheck -= _DeltaTime;

	//	if (DeathTimeCheck <= 0.f)
	//	{
	//		DeathTimeStart = false;
	//		Death = true;
	//	}
	//}

	//AddActorLocation(Dir * Speed * _DeltaTime);	
}


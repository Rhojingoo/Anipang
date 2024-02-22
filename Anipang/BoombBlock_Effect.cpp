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
	AActor::BeginPlay();

	#pragma region �׽�Ʈ �ڵ�
	//�ٸ� �̹���
	//Renderer = CreateImageRenderer(10);
	//Renderer->SetImage("Phoenix Landing");
	//Renderer->SetTransform({ {100,200}, {75, 200} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {70, 250} });
	//Renderer->CreateAnimation("Idle", "Phoenix Landing", 0, 6, 0.1f, true);
	//Renderer->ChangeAnimation("Idle");
#pragma endregion

	{
		Renderer = CreateImageRenderer(20);
		Renderer->SetImage("Boomb_Effect");
		Renderer->SetTransform({ {0,-175}, {135, 350} });
		Renderer->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
		Renderer->ChangeAnimation("Idle");
	}

}

void ABoombBlock_Effect::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (GetActorLocation().Y >= 685.f)
	{
		Destroy(0.f);		
	}


	////ȸ����
	//static float Angle = 0.0f;
	//Angle += _DeltaTime * 360.0f;
	//Renderer->SetAngle(Angle);


	////������
	//FVector Dir = { 100.0f, -100.0f };
	//Dir.RotationZToDeg(-45.0f);
	////static float Angle = 0.0f;
	////Angle += _DeltaTime * 360.0f;
	//Renderer->SetPosition(Dir);


	if (SideRender == true)
	{
		Renderer->SetTransform({ {0,0}, {135, 350} });
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


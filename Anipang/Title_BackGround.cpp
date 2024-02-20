#include "Title_BackGround.h"

float ATitle_BackGround::AlphaTime = 0.f;
ATitle_BackGround::ATitle_BackGround()
{
}

ATitle_BackGround::~ATitle_BackGround()
{
}

void ATitle_BackGround::BeginPlay()
{
	AActor::BeginPlay();

	
	//타이틀 배경  애니메이션
	Renderer = CreateImageRenderer(0);
	Renderer->SetImage("Intro_BG");
	SetActorLocation({ 240, 400 });
	//Renderer->SetTransColor(Color8Bit::Magenta.ZeroAlphaColor());
	Renderer->SetTransform({ {0,0}, {480, 800} });
	Renderer->SetImageCuttingTransform({ {0,0}, {480, 800} });
	Renderer->CreateAnimation("Idle", "Intro_BG", 0, 3, 1.25f, false);
	//Renderer->CreateAnimation("Idle", "Intro_BG", 0, 3, 1.55f, false);
	Renderer->ChangeAnimation("Idle");
	

#pragma region 테스트 이미지

	{
		//  타이틀 오브젝트 블럭Effect
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Block_Effect");	
		//Renderer2->SetTransform({ {100,200}, {133, 139} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Block_Effect", 0, 4, 0.1f, true);
		////Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	{
		//  타이틀 오브젝트 폭탄Effect
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Boomb_Effect");
		////Renderer2->SetTransColor(Color8Bit::Magenta.ZeroAlphaColor());
		//Renderer2->SetTransform({ {100,200}, {155, 265} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {155, 265} });
		//Renderer2->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
		////Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer2->ChangeAnimation("Idle");
	}
#pragma endregion


}

void ATitle_BackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (FinalAnimation == false)
	{
		AlphaSetting(_DeltaTime);
	}
}

void ATitle_BackGround::AlphaSetting(float _DeltaTime)
{

		AlphaTime += _DeltaTime;
		if (AlphaTime < 4.5)
		{
			CheckTime += _DeltaTime;
			if (1.1f <= CheckTime)
			{
				Dir = !Dir;
				CheckTime = 0.0f;
			}
			if (true == Dir)
			{
				Renderer->SetAlpha(CheckTime * 0.15f);
			}
			else
			{
				Renderer->SetAlpha(1.0f - CheckTime);
			}
		}
		else
		{
			Renderer->SetAlpha(1.0f);
			FinalAnimation = true;
		}	
}

#include "Play_Frame.h"

APlay_Frame::APlay_Frame()
{
}

APlay_Frame::~APlay_Frame()
{
}

void APlay_Frame::BeginPlay()
{
	AActor::BeginPlay();
	{
		// 타이틀 배경
		Renderer = CreateImageRenderer(0);
		Renderer->SetImage("PlayFrame2.png");
		SetActorLocation({ 240, 400 });
		Renderer->SetTransform({ {-8,0}, {464, 800} });
		//Renderer->SetImageCuttingTransform({ {0,0}, {367, 609} });
	}

	{
		// 스프라이트 블럭이미지 확정
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Rabbit");
		//Renderer2->SetTransform({ {100,200}, {75, 75} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Rabbit", 0, 2, 1.1f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	{
		// 스프라이트 테스트이미지
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Boomb_Effect");
		//Renderer2->SetTransform({ {100,200}, {135, 350} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {135, 350} });
		//Renderer2->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.2f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	
	{
		// 스프라이트 테스트이미지
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("World_On_Fire_Projectile");
		//Renderer2->SetTransform({ {100,200}, {75, 75} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {110, 62} });
		//Renderer2->CreateAnimation("Idle", "World_On_Fire_Projectile", 0, 23, 0.2f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	{
		// 스프라이트 테스트이미지
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Fireball_Projectile");
		//Renderer2->SetTransform({ {100,200}, {75, 75} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {46, 28} });
		//Renderer2->CreateAnimation("Idle", "Fireball_Projectile", 0, 11, 0.2f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	{
		// 스프라이트 테스트이미지
		UImageRenderer* Renderer2 = CreateImageRenderer(1);
		Renderer2->SetImage("Phoenix Landing");
		Renderer2->SetTransform({ {100,200}, {75, 200} });
		Renderer2->SetImageCuttingTransform({ {0,0}, {70, 250} });
		Renderer2->CreateAnimation("Idle", "Phoenix Landing", 0, 6, 0.1f, true);
		Renderer2->ChangeAnimation("Idle");
	}

}

void APlay_Frame::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

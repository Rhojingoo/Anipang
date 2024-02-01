#include "Title_BackGround.h"

ATitle_BackGround::ATitle_BackGround()
{
}

ATitle_BackGround::~ATitle_BackGround()
{
}

void ATitle_BackGround::BeginPlay()
{
	AActor::BeginPlay();

	{
		// �̹��� ���� ����
		//Renderer = CreateImageRenderer(0);
		//Renderer->SetImage("Cat00.png");
		//SetActorLocation({ 50, 50 });
		//Renderer->SetTransform({ {50,50}, {50, 50} });
		//Renderer->SetImageCuttingTransform({ {0,0}, {80, 80} });
	}

	{
		// Ÿ��Ʋ ���
		Renderer = CreateImageRenderer(0);
		Renderer->SetImage("Intro_BG");  
		SetActorLocation({ 240, 400 });
		Renderer->SetTransform({ {0,0}, {480, 800} });
		Renderer->SetImageCuttingTransform({ {0,0}, {480, 800} });
		Renderer->CreateAnimation("Idle", "Intro_BG", 0, 2, 1.f, true);
		Renderer->ChangeAnimation("Idle");
	}


	{
		//  Ÿ��Ʋ ������Ʈ
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Intro_OBJ");	
		//Renderer2->SetTransform({ {100,200}, {133, 139} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Intro_OBJ", 0, 1, 0.1f, true);
		////Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	{
		// ��������Ʈ �׽�Ʈ�̹���
		UImageRenderer* Renderer2 = CreateImageRenderer(1);
		Renderer2->SetImage("Cat");	
		Renderer2->SetTransform({ {100,200}, {133, 139} });
		Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		Renderer2->CreateAnimation("Idle", "Cat", 0, 2, 0.1f, true);
		Renderer2->ChangeAnimation("Idle");
	}


	{
		// ��������Ʈ �׽�Ʈ�̹���
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Intro_OBJ");	
		//Renderer2->SetTransform({ {100,200}, {133, 139} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Intro_OBJ", 0, 1, 0.1f, true);
		//Renderer2->ChangeAnimation("Idle");
	}



}

void ATitle_BackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

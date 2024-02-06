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

#pragma region bejuweled
	
	//// Ÿ��Ʋ ���
	//	Renderer = CreateImageRenderer(0);
	//	Renderer->SetImage("gameselector_bg.png");
	//	SetActorLocation({ 512, 245 });
	//	Renderer->SetTransform({ {0,0}, {1024, 570} });
	//	Renderer->SetImageCuttingTransform({ {0,0}, {1024, 570} });
	//
	////  Ÿ��Ʋ ������Ʈ ��Effect
	//	UImageRenderer* Renderer2 = CreateImageRenderer(1);
	//	Renderer2->SetImage("Topaz.png");	
	//	Renderer2->SetTransform({ {100,200}, {84, 84} });
	//	Renderer2->SetImageCuttingTransform({ {0,0}, {84, 84} });
	//	Renderer2->CreateAnimation("Idle", "Topaz.png", 0, 19, 0.1f, true);
	//	Renderer2->ChangeAnimation("Idle");	
#pragma endregion

#pragma region anipang 
	{
		// �̹��� ���� ����
		//Renderer = CreateImageRenderer(1);
		//Renderer->SetImage("boom2.png");
		//SetActorLocation({ 50, 50 });
		//Renderer->SetTransform({ {50,50}, {50, 50} });
		//Renderer->SetImageCuttingTransform({ {0,0}, {80, 80} });
	}

	{
		 //Ÿ��Ʋ ���  �ִϸ��̼�
		Renderer = CreateImageRenderer(0);
		Renderer->SetImage("Intro_BG");
		SetActorLocation({ 240, 400 });
		//Renderer->SetTransColor(Color8Bit::Magenta.ZeroAlphaColor());
		Renderer->SetTransform({ {0,0}, {480, 800} });
		Renderer->SetImageCuttingTransform({ {0,0}, {480, 800} });
		Renderer->CreateAnimation("Idle", "Intro_BG", 0, 2, 1.5f, false);
		Renderer->ChangeAnimation("Idle");
	}

	{
		//  Ÿ��Ʋ ������Ʈ �ִϸ��̼�
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Intro_OBJ");	
		//SetActorLocation({ 240, 400 });
		//Renderer2->SetTransform({ {20,100}, {100, 105} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Intro_OBJ", 0, 1, 0.1f, true);
		////Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer2->ChangeAnimation("Idle");
	}

	{
		// // Ÿ��Ʋ ������Ʈ�ΰ�
		//UImageRenderer* Renderer = CreateImageRenderer(2);
		//Renderer->SetImage("Intro_Logo2.png");
		//SetActorLocation({ 240, 400 });
		////Renderer->SetTransColor(Color8Bit::Magenta.ZeroAlphaColor());
		//Renderer->SetTransform({ {10,-185}, {400, 300} });
		//Renderer->SetImageCuttingTransform({ {0,0}, {445, 356} });
	}


#pragma endregion

#pragma region �׽�Ʈ �̹���

	{
		//  Ÿ��Ʋ ������Ʈ ��Effect
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Block_Effect");	
		//Renderer2->SetTransform({ {100,200}, {133, 139} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Block_Effect", 0, 4, 0.1f, true);
		////Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer2->ChangeAnimation("Idle");
	}


	{
		//  Ÿ��Ʋ ������Ʈ ��źEffect
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Boomb_Effect");
		////Renderer2->SetTransColor(Color8Bit::Magenta.ZeroAlphaColor());
		//Renderer2->SetTransform({ {100,200}, {155, 265} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {155, 265} });
		//Renderer2->CreateAnimation("Idle", "Boomb_Effect", 0, 6, 0.1f, true);
		////Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer2->ChangeAnimation("Idle");
	}


	//{
	//	// ��������Ʈ �׽�Ʈ�̹���
	//	UImageRenderer* Renderer2 = CreateImageRenderer(1);
	//	Renderer2->SetImage("Cat");
	//	Renderer2->SetTransform({ {100,200}, {133, 139} });
	//	Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
	//	Renderer2->CreateAnimation("Idle", "Cat", 0, 2, 1.1f, true);
	//	Renderer2->ChangeAnimation("Idle");
	//}


	{
		// ��������Ʈ �׽�Ʈ�̹���
		//UImageRenderer* Renderer2 = CreateImageRenderer(1);
		//Renderer2->SetImage("Intro_OBJ");	
		//Renderer2->SetTransform({ {100,200}, {133, 139} });
		//Renderer2->SetImageCuttingTransform({ {0,0}, {133, 139} });
		//Renderer2->CreateAnimation("Idle", "Intro_OBJ", 0, 1, 0.1f, true);
		//Renderer2->ChangeAnimation("Idle");
	}
#pragma endregion


}

void ATitle_BackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AlphaSetting(_DeltaTime);
}

void ATitle_BackGround::AlphaSetting(float _DeltaTime)
{
	AlphaTime += _DeltaTime;
	if (AlphaTime < 3.5)
	{
		CheckTime += _DeltaTime;
		if (1.0f <= CheckTime)
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

#include "Animal_Block.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include "TestBullet.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>

AAnimal_Block::AAnimal_Block()
{
}

AAnimal_Block::~AAnimal_Block()
{
}

void AAnimal_Block::BeginPlay()
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
		// �̹����� �����͵�
		//Renderer = CreateImageRenderer();
		//Renderer->SetImage("TestFolderAni");
		//SetActorLocation({ 200, 200 });
		//Renderer->SetTransform({ {0,0}, {100, 100} });
		//Renderer->SetImageCuttingTransform({ {64,64}, {32, 32} });
	}
	{
		// ��������Ʈ �̹���
		//Renderer = CreateImageRenderer();
		//Renderer->SetImage("TestSpriteAni.png");
		//SetActorLocation({ 200, 200 });
		//Renderer->SetTransform({ {50,50}, {100, 100} });
		//Renderer->SetImageCuttingTransform({ {64,64}, {32, 32} });
		//Renderer->CreateAnimation("Idle", "TestSpriteAni.png", 0, 12, 0.5f, true);
		//Renderer->CreateAnimation("Attack", "TestSpriteAni.png", 26, 32, 0.5f, true);
		//Renderer->ChangeAnimation("Idle");
	}

}

void AAnimal_Block::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

#pragma region �׽�Ʈ �ڵ�
	//if (true == UEngineInput::IsPress('A'))
	//{
	//	AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('D'))
	//{
	//	AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('W'))
	//{
	//	AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('S'))
	//{
	//	AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('Q'))
	//{
	//	Renderer->ChangeAnimation("Attack");
	//}


	//if (true == UEngineInput::IsDown(VK_LBUTTON))
	//{
	//	ATestBullet* NewBullet = GetWorld()->SpawnActor<ATestBullet>();
	//	NewBullet->SetActorLocation(GetActorLocation());
	//	NewBullet->SetDir(FVector::Right);
	//}


#pragma endregion
}

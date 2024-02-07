
#include "Rabbit_Block.h"

ARabbit_Block::ARabbit_Block()
{
}

ARabbit_Block::~ARabbit_Block()
{
}

void ARabbit_Block::BeginPlay()
{
	AActor::BeginPlay();
	UImageRenderer* Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Rabbit");
	Renderer->SetTransform({ {0,0}, {75, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Rabbit", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("Click", "Rabbit", 1, 1, 1.1f, true);
	Renderer->CreateAnimation("Boomb", "Rabbit", 0, 2, 0.3f, true);
	Renderer->ChangeAnimation("Idle");
}

void ARabbit_Block::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();

	switch (Blockstatus)
	{
	case AAnimal_Block::Block_Status::Idle:
	{
		if (BlockClick == true)
		{
			Renderer->ChangeAnimation("Click");
			Blockstatus = Block_Status::Click;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Click:
	{
		if (BlockClick == false)
		{
			Renderer->ChangeAnimation("Idle");
			Blockstatus = Block_Status::Idle;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Boomb:
	{
	}
	break;
	case AAnimal_Block::Block_Status::End:
		break;
	default:
		break;
	}
}
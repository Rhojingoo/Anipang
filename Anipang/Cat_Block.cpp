#include "Cat_Block.h"

ACat_Block::ACat_Block()
{
}

ACat_Block::~ACat_Block()
{
}

void ACat_Block::BeginPlay()
{
	AAnimal_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Cat");
	Renderer->SetTransform({ {0,0}, {75, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Cat", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("Click", "Cat", 1,1, 1.1f, true);
	Renderer->CreateAnimation("Boomb", "Cat", 0, 2, 0.3f, true);
	Renderer->ChangeAnimation("Idle");

}

void ACat_Block::Tick(float _DeltaTime)
{
	AAnimal_Block::Tick(_DeltaTime);
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
			int RenderNumber = 2;
			Renderer->SetOrder(RenderNumber);
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
			int RenderNumber = 1;
			Renderer->SetOrder(RenderNumber);
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

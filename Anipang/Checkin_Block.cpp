#include "Checkin_Block.h"

ACheckin_Block::ACheckin_Block()
{
}

ACheckin_Block::~ACheckin_Block()
{
}

void ACheckin_Block::BeginPlay()
{
	AAnimal_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Checkin");
	Renderer->SetTransform({ {0,0}, {75, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Checkin", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("Click", "Checkin", 1, 1, 1.1f, true);
	Renderer->CreateAnimation("Boomb", "Checkin", 0, 2, 0.3f, true);
	Renderer->ChangeAnimation("Idle");
	Blocktype = Block_Type::Checkin;

}

void ACheckin_Block::Tick(float _DeltaTime)
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
			return;
		}

		if (BoombBlock == true)
		{
			Renderer->ChangeAnimation("Boomb");
			Blockstatus = Block_Status::Boomb;
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

		if (BoombBlock == true)
		{
			Renderer->ChangeAnimation("Boomb");
			Blockstatus = Block_Status::Boomb;
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
#include "Mouse_Block.h"

AMouse_Block::AMouse_Block()
{
}

AMouse_Block::~AMouse_Block()
{
}

void AMouse_Block::BeginPlay()
{
	AAnimal_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Mouse");
	Renderer->SetTransform({ {0,0}, {75, 75} });
	Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	Renderer->CreateAnimation("Idle", "Mouse", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("Click", "Mouse", 1, 1, 1.1f, true);
	Renderer->CreateAnimation("Boomb", "Mouse", 0, 2, 0.1f, false);
	Renderer->ChangeAnimation("Idle");
	Blocktype = Block_Type::Mouse;
}

void AMouse_Block::Tick(float _DeltaTime)
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

		if (BoombBlock == true)
		{
			Renderer->ChangeAnimation("Boomb");
			Blockstatus = Block_Status::Boomb;
			return;
		}

		if (UnderBlockBoomb == true)
		{
			Blockstatus = Block_Status::Move;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Move:
	{
		if (Pos.Y >= UnderPos.Y)
		{
			SetUnderBoomb(false);
			Pos.Y = UnderPos.Y;
			Blockstatus = Block_Status::Idle;
			return;
		}
		AddActorLocation({ FVector::Down * 150.0f * _DeltaTime });
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

		if (BoombBlock == true)
		{
			Renderer->ChangeAnimation("Boomb");
			Blockstatus = Block_Status::Boomb;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Boomb:
	{
		bool AnimationEnd = Renderer->IsCurAnimationEnd();
		if (AnimationEnd == true)
		{
			CreateBlockEffect();
			Destroy(0.f);
		}
	}
	break;
	case AAnimal_Block::Block_Status::End:
		break;
	default:
		break;
	}
}
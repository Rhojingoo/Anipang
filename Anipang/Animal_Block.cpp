#include "Animal_Block.h"

AAnimal_Block::AAnimal_Block()
{
}

AAnimal_Block::~AAnimal_Block()
{
}

void AAnimal_Block::BeginPlay()
{
	ABase_Block::BeginPlay();

	{
		Renderer = CreateImageRenderer(1);
		Renderer->SetTransform({ {0,0}, {75, 75} });
		Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });

		//Renderer->SetImage("Cat");
		Renderer->CreateAnimation("Cat_Idle", "Cat", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Cat_Click", "Cat", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Cat_Bomb", "Cat", 0, 2, 0.1f, false);


		//Renderer->SetImage("Checkin");
		Renderer->CreateAnimation("Checkin_Idle", "Checkin", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Checkin_Click", "Checkin", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Checkin_Bomb", "Checkin", 0, 2, 0.1f, false);
		
		//Renderer->SetImage("Dog");
		Renderer->CreateAnimation("Dog_Idle", "Dog", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Dog_Click", "Dog", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Dog_Bomb", "Dog", 0, 2, 0.1f, false);

		//Renderer->SetImage("Monkey");
		Renderer->CreateAnimation("Monkey_Idle", "Monkey", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Monkey_Click", "Monkey", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Monkey_Bomb", "Monkey", 0, 2, 0.1f, false);

		//Renderer->SetImage("Mouse");
		Renderer->CreateAnimation("Mouse_Idle", "Mouse", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Mouse_Click", "Mouse", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Mouse_Bomb", "Mouse", 0, 2, 0.1f, false);

		//Renderer->SetImage("Pig");
		Renderer->CreateAnimation("Pig_Idle", "Pig", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Pig_Click", "Pig", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Pig_Bomb", "Pig", 0, 2, 0.1f, false);

		//Renderer->SetImage("Rabbit");
		Renderer->CreateAnimation("Rabbit_Idle", "Rabbit", 0, 0, 1.1f, true);
		Renderer->CreateAnimation("Rabbit_Click", "Rabbit", 1, 1, 1.1f, true);
		Renderer->CreateAnimation("Rabbit_Bomb", "Rabbit", 0, 2, 0.1f, false);
	}
	Renderer->ChangeAnimation("Cat_Idle");	
}

void AAnimal_Block::Tick(float _DeltaTime)
{
	ABase_Block::Tick(_DeltaTime);	

	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();

	if (FirstImageSelect == false)
	{
		if (Blocktype == Block_Type::Cat)
		{
			Renderer->ChangeAnimation("Cat_Idle");
		}
		else if (Blocktype == Block_Type::Checkin)
		{
			Renderer->ChangeAnimation("Checkin_Idle");
		}
		else if (Blocktype == Block_Type::Dog)
		{
			Renderer->ChangeAnimation("Dog_Idle");
		}
		else if (Blocktype == Block_Type::Monkey)
		{
			Renderer->ChangeAnimation("Monkey_Idle");
		}
		else if (Blocktype == Block_Type::Mouse)
		{
			Renderer->ChangeAnimation("Mouse_Idle");
		}
		else if (Blocktype == Block_Type::Pig)
		{
			Renderer->ChangeAnimation("Pig_Idle");
		}
		else if (Blocktype == Block_Type::Rabbit)
		{
			Renderer->ChangeAnimation("Rabbit_Idle");
		}
		FirstImageSelect = true;
	}


	switch (Blockstatus)
	{
	case ABase_Block::Block_Status::Idle:
	{
		if (BlockClick == true)
		{
			if (Blocktype == Block_Type::Cat)
			{
				Renderer->ChangeAnimation("Cat_Click");
			}
			else if (Blocktype == Block_Type::Checkin)
			{
				Renderer->ChangeAnimation("Checkin_Click");
			}
			else if (Blocktype == Block_Type::Dog)
			{
				Renderer->ChangeAnimation("Dog_Click");
			}
			else if (Blocktype == Block_Type::Monkey)
			{
				Renderer->ChangeAnimation("Monkey_Click");
			}
			else if (Blocktype == Block_Type::Mouse)
			{
				Renderer->ChangeAnimation("Mouse_Click");
			}
			else if (Blocktype == Block_Type::Pig)
			{
				Renderer->ChangeAnimation("Pig_Click");
			}
			else if (Blocktype == Block_Type::Rabbit)
			{
				Renderer->ChangeAnimation("Rabbit_Click");
			}

			
			Blockstatus = Block_Status::Click;
			int RenderNumber = 2;
			Renderer->SetOrder(RenderNumber);
			return;
		}

		if (BoombBlock == true)
		{
			CreateBlockEffect();
			UEngineSound::SoundPlay("Block_BOOM.mp3");

			if (Blocktype == Block_Type::Cat)
			{
				Renderer->ChangeAnimation("Cat_Bomb");
			}
			else if (Blocktype == Block_Type::Checkin)
			{
				Renderer->ChangeAnimation("Checkin_Bomb");
			}
			else if (Blocktype == Block_Type::Dog)
			{
				Renderer->ChangeAnimation("Dog_Bomb");
			}
			else if (Blocktype == Block_Type::Monkey)
			{
				Renderer->ChangeAnimation("Monkey_Bomb");
			}
			else if (Blocktype == Block_Type::Mouse)
			{
				Renderer->ChangeAnimation("Mouse_Bomb");
			}
			else if (Blocktype == Block_Type::Pig)
			{
				Renderer->ChangeAnimation("Pig_Bomb");
			}
			else if (Blocktype == Block_Type::Rabbit)
			{
				Renderer->ChangeAnimation("Rabbit_Bomb");
			}
	
			Blockstatus = Block_Status::Bomb;
			FindEnd = true;
			return;
		}

		if (UnderBlockBoomb == true)
		{
			Blockstatus = Block_Status::Move;
			return;
		}

		if (LetsFind == true)
		{
			Blockstatus = Block_Status::Find;
			return;
		}
	}
	break;
	case ABase_Block::Block_Status::Move:
	{
		if (Pos.Y >= UnderPos.Y)
		{
			SetUnderBoomb(false);
			Pos.Y = UnderPos.Y;
			Blockstatus = Block_Status::Idle;
			return;
		}
		AddActorLocation({ FVector::Down * DownSpeed * _DeltaTime });
	}
	break;
	case ABase_Block::Block_Status::Click:
	{

		if (BlockClick == false)
		{	
			if (Blocktype == Block_Type::Cat)
			{
				Renderer->ChangeAnimation("Cat_Idle");
			}
			else if (Blocktype == Block_Type::Checkin)
			{
				Renderer->ChangeAnimation("Checkin_Idle");
			}
			else if (Blocktype == Block_Type::Dog)
			{
				Renderer->ChangeAnimation("Dog_Idle");
			}
			else if (Blocktype == Block_Type::Monkey)
			{
				Renderer->ChangeAnimation("Monkey_Idle");
			}
			else if (Blocktype == Block_Type::Mouse)
			{
				Renderer->ChangeAnimation("Mouse_Idle");
			}
			else if (Blocktype == Block_Type::Pig)
			{
				Renderer->ChangeAnimation("Pig_Idle");
			}
			else if (Blocktype == Block_Type::Rabbit)
			{
				Renderer->ChangeAnimation("Rabbit_Idle");
			}
			Blockstatus = Block_Status::Idle;
			int RenderNumber = 1;
			Renderer->SetOrder(RenderNumber);

			if (SecondPick == true)
			{
				SecondClick = false;
				SecondPick = false;
			}
			if (FirstPick == true)
			{
				FirstClick = false;
				FirstPick = false;
			}

			return;
		}

		if (BoombBlock == true)
		{
			CreateBlockEffect();
			UEngineSound::SoundPlay("Block_BOOM.mp3");
			if (Blocktype == Block_Type::Cat)
			{
				Renderer->ChangeAnimation("Cat_Bomb");
			}
			else if (Blocktype == Block_Type::Checkin)
			{
				Renderer->ChangeAnimation("Checkin_Bomb");
			}
			else if (Blocktype == Block_Type::Dog)
			{
				Renderer->ChangeAnimation("Dog_Bomb");
			}
			else if (Blocktype == Block_Type::Monkey)
			{
				Renderer->ChangeAnimation("Monkey_Bomb");
			}
			else if (Blocktype == Block_Type::Mouse)
			{
				Renderer->ChangeAnimation("Mouse_Bomb");
			}
			else if (Blocktype == Block_Type::Pig)
			{
				Renderer->ChangeAnimation("Pig_Bomb");
			}
			else if (Blocktype == Block_Type::Rabbit)
			{
				Renderer->ChangeAnimation("Rabbit_Bomb");
			}
			Blockstatus = Block_Status::Bomb;
			FindEnd = true;
			return;
		}
	}
	break;
	case ABase_Block::Block_Status::Bomb:
	{

		bool AnimationEnd = Renderer->IsCurAnimationEnd();
		if (AnimationEnd == true)
		{
			/*CreateBlockEffect();*/
			FindEnd = true;
			Destroy(0.f);
		}
	}
	break;

	case ABase_Block::Block_Status::Find:
	{
		FindTime += _DeltaTime;
		if (1.f <= FindTime)
		{
			AlphaBlend = !AlphaBlend;
			FindTime = 0.0f;
		}
		if (true == AlphaBlend)
		{
			Renderer->SetAlpha(FindTime * 0.45f);
		}
		else
		{
			Renderer->SetAlpha(1.0f - FindTime);
		}

		if (LetsFind == false)
		{
			Blockstatus = Block_Status::Idle;
			Renderer->SetAlpha(1.0f);
			return;
		}

		if (BlockClick == true)
		{
			if (Blocktype == Block_Type::Cat)
			{
				Renderer->ChangeAnimation("Cat_Click");
			}
			else if (Blocktype == Block_Type::Checkin)
			{
				Renderer->ChangeAnimation("Checkin_Click");
			}
			else if (Blocktype == Block_Type::Dog)
			{
				Renderer->ChangeAnimation("Dog_Click");
			}
			else if (Blocktype == Block_Type::Monkey)
			{
				Renderer->ChangeAnimation("Monkey_Click");
			}
			else if (Blocktype == Block_Type::Mouse)
			{
				Renderer->ChangeAnimation("Mouse_Click");
			}
			else if (Blocktype == Block_Type::Pig)
			{
				Renderer->ChangeAnimation("Pig_Click");
			}
			else if (Blocktype == Block_Type::Rabbit)
			{
				Renderer->ChangeAnimation("Rabbit_Click");
			}
			Blockstatus = Block_Status::Click;
			int RenderNumber = 2;
			Renderer->SetOrder(RenderNumber);
			Renderer->SetAlpha(1.0f);
			FindEnd = true;
			LetsFind = false;
			return;
		}

		if (BoombBlock == true)
		{
			CreateBlockEffect();
			UEngineSound::SoundPlay("Block_BOOM.mp3");
			if (Blocktype == Block_Type::Cat)
			{
				Renderer->ChangeAnimation("Cat_Bomb");
			}
			else if (Blocktype == Block_Type::Checkin)
			{
				Renderer->ChangeAnimation("Checkin_Bomb");
			}
			else if (Blocktype == Block_Type::Dog)
			{
				Renderer->ChangeAnimation("Dog_Bomb");
			}
			else if (Blocktype == Block_Type::Monkey)
			{
				Renderer->ChangeAnimation("Monkey_Bomb");
			}
			else if (Blocktype == Block_Type::Mouse)
			{
				Renderer->ChangeAnimation("Mouse_Bomb");
			}
			else if (Blocktype == Block_Type::Pig)
			{
				Renderer->ChangeAnimation("Pig_Bomb");
			}
			else if (Blocktype == Block_Type::Rabbit)
			{
				Renderer->ChangeAnimation("Rabbit_Bomb");
			}
			Blockstatus = Block_Status::Bomb;
			Renderer->SetAlpha(1.0f);
			FindEnd = true;
			return;
		}

		if (UnderBlockBoomb == true)
		{
			Blockstatus = Block_Status::Move;
			Renderer->SetAlpha(1.0f);
			FindEnd = true;
			LetsFind = false;
			return;
		}
	}
	break;

	case ABase_Block::Block_Status::End:
		break;
	default:
		break;
	}
}

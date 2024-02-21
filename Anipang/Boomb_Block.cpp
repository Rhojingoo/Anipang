#include "Boomb_Block.h"
#include "TestBullet.h"


ABoomb_Block::ABoomb_Block()
{
}

ABoomb_Block::~ABoomb_Block()
{
}

void ABoomb_Block::BeginPlay()
{
	AAnimal_Block::BeginPlay();
	Renderer = CreateImageRenderer(1);
	Renderer->SetImage("boom.png");
	Renderer->SetTransform({ {0,0}, {55, 55} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {133, 139} });
	//Renderer->CreateAnimation("Idle", "Cat", 0, 0, 1.1f, true);
	//Renderer->CreateAnimation("Click", "Cat", 1, 1, 1.1f, true);
	//Renderer->CreateAnimation("Boomb", "Cat", 0, 2, 0.1f, false);
	//Renderer->ChangeAnimation("Idle");
	Blocktype = Block_Type::Boomb;
}

void ABoomb_Block::Tick(float _DeltaTime)
{
	AAnimal_Block::Tick(_DeltaTime);
	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();

	CollCheck_First_Effect();

	


	switch (Blockstatus)
	{
	case AAnimal_Block::Block_Status::Idle:
	{
		if (BlockClick == true)
		{			
			Blockstatus = Block_Status::Click;
			Create_First_Effect();
			// ������Ʈ ����� Ŭ������ ����������.
			BlockClick = false;
		
			// �غ�����Ʈ ������ ����(�������)
			// ������Ʈ�� ���� ����� ��ġ���� ���������� ó���ϸ�.
			// ���� �������� �� �ٸ� ����Ʈ�� �����Ѵ�.
			// 
			// => ����1. ��ź���� Ŭ���ϸ� ��ź���� ������X�� ��ǥ�� ���ʿ��� ù ����Ʈ�� ���������̴�.
			// => ����2. ù ����Ʈ�� ��ź���� ������������ �ٸ����� �����ٸ� �ٸ������� �������̴�.
			// => ����3. ��ź���� ù ����Ʈ�� �����ٸ� �ι�° ����Ʈ���� �����ϰ� �Ǹ� ��ź�� ��ġ������ 3����, 2����, 1���� ���� �����Ǿ� �߻�ɰ��̴�.
			// => ����4. ��ź���� ������ �ִٸ� ���� �������� �� �ݴ� �������θ� ����Ʈ ���� �� �߻��Ѵ�.
			// => ����5. ��ź���� ���� �پ����� �ʴٸ� ���� �������� �������� �߻� �����ϴ�.
			// => ����6. ��ź���� �߾ӿ� �ִٸ� �Ʒ�����, �翷�������� ����Ʈ�� ���� �� �߻��Ѵ�.
			// => ����7. �ι�° ����Ʈ�鵵 �ٸ����� ������ �Ǹ� �ٸ������� �������̴�.
	

			//int RenderNumber = 2;
			//Renderer->SetOrder(RenderNumber);
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
		AddActorLocation({ FVector::Down * DownSpeed * _DeltaTime });
	}
	break;
	case AAnimal_Block::Block_Status::Click:
	{
		if (BoombBlock == true)
		{
			Blockstatus = Block_Status::Boomb;
			return;
		}
	}
	break;
	case AAnimal_Block::Block_Status::Boomb:
	{
		// �պ��� �������� ����Ʈ �������븸�̴�.
		// �պ��� �÷��̷������� Destroycheck�� ������ ��Ȳ�� ������ ���� ó�� �Ұ�!
		Destroy(0.f);		
	}
	break;
	case AAnimal_Block::Block_Status::End:
		break;
	default:
		break;
	}



}

void ABoomb_Block::Create_First_Effect()
{
	First_Effect = GetWorld()->SpawnActor<ATestBullet>();
	int col = GetBlockLocationCol();
	int row = 0;
	FVector SetPos = GetBlockFVector(col, row);

	int a = 0;
	First_Effect->SetActorLocation(SetPos);
	First_Effect->SetDir(FVector::Down);
	FirstEffect_Create = true;
}

void ABoomb_Block::CollCheck_First_Effect()
{
	if (FirstEffect_Create == true)
	{
		FVector abctest = First_Effect->GetActorLocation();

		float MinX = Pos.X - Size.X / 2;
		float MinY = Pos.Y - Size.Y / 2;
		float MaxX = Pos.X + Size.X / 2;
		float MaxY = Pos.Y + Size.Y / 2;
		int a = 0;
		if (abctest.X >= MinX && abctest.X <= MaxX && abctest.Y - 75.f >= MinY && abctest.Y - 75.f <= MaxY)
		{
			// �ݸ��� üũ �ϸ鼭 ������� row�� col�� �޾Ƽ� ������ �ް�.
			// row�� col�� ��ġ������ left���� right����, down���� ���ؼ� ����� �����ٰ�.

			int Row = GetBlockLocationRow();
			int Col = GetBlockLocationCol();

			int a = 0;

			if (Col == 0)
			{
				{
					Right_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Right_Effect->SetActorLocation(SetPos);
					Right_Effect->SetDir(FVector::Right);
				}

				{
					Down_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Down_Effect->SetActorLocation(SetPos);
					Down_Effect->SetDir(FVector::Down);
				}

			}
			else if (Row == 6 && Col == 0)
			{
				Right_Effect = GetWorld()->SpawnActor<ATestBullet>();
				FVector SetPos = GetActorLocation();
				Right_Effect->SetActorLocation(SetPos);
				Right_Effect->SetDir(FVector::Right);
			}
			else if (Row == 6 && Col == 6)
			{
				Left_Effect = GetWorld()->SpawnActor<ATestBullet>();
				FVector SetPos = GetActorLocation();
				Left_Effect->SetActorLocation(SetPos);
				Left_Effect->SetDir(FVector::Left);
			}
			else if (Col == 6)
			{
				{
					Left_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Left_Effect->SetActorLocation(SetPos);
					Left_Effect->SetDir(FVector::Left);
				}
				{
					Down_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Down_Effect->SetActorLocation(SetPos);
					Down_Effect->SetDir(FVector::Down);
				}
			}
			else if (Row == 6)
			{ 
				{
					Left_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Left_Effect->SetActorLocation(SetPos);
					Left_Effect->SetDir(FVector::Left);
				}
	
				{
					Right_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Right_Effect->SetActorLocation(SetPos);
					Right_Effect->SetDir(FVector::Right);
				}
			}
			
			else
			{
				{
					Right_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Right_Effect->SetActorLocation(SetPos);
					Right_Effect->SetDir(FVector::Right);
				}

				{
					Left_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Left_Effect->SetActorLocation(SetPos);
					Left_Effect->SetDir(FVector::Left);
				}

				{
					Down_Effect = GetWorld()->SpawnActor<ATestBullet>();
					FVector SetPos = GetActorLocation();
					Down_Effect->SetActorLocation(SetPos);
					Down_Effect->SetDir(FVector::Down);
				}
			}

			First_Effect->Destroy(0.0f);
			FirstEffect_Create = false;		
		}
	}
}


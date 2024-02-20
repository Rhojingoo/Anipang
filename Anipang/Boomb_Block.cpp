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
	Renderer->SetTransform({ {0,0}, {35, 35} });
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

	switch (Blockstatus)
	{
	case AAnimal_Block::Block_Status::Idle:
	{
		if (BlockClick == true)
		{			
			//Blockstatus = Block_Status::Click;
			Create_First_Effect();
			// 블럭이펙트 만들고 클릭으로 보내버린다.
			BlockClick = false;
		
			// ※블럭이펙트 생성시 조건(고려사항)
			// 블럭이펙트는 블럭이 생기는 위치에서 떨어지도록 처리하며.
			// 블럭과 만났을때 또 다른 이펙트를 생성한다.
			// 
			// => 조건1. 폭탄블럭을 클릭하면 폭탄블럭의 동일한X값 좌표의 위쪽에서 첫 이펙트가 떨어질것이다.
			// => 조건2. 첫 이펙트는 폭탄블럭과 만나기전까지 다른블럭을 만난다면 다른블럭들은 터질것이다.
			// => 조건3. 폭탄블럭과 첫 이펙트가 만난다면 두번째 이펙트들을 생성하게 되며 폭탄블럭 위치에따라 3방향, 2방향, 1방향 으로 생성되어 발사될것이다.
			// => 조건4. 폭탄블럭이 벽끝에 있다면 블럭과 만났을때 벽 반대 방향으로만 이펙트 생성 후 발사한다.
			// => 조건5. 폭탄블럭이 벽에 붙어있지 않다면 블럭과 만났을때 양쪽으로 발사 가능하다.
			// => 조건6. 폭탄블럭이 중앙에 있다면 아래방향, 양옆방향으로 이펙트를 생성 후 발사한다.
			// => 조건7. 두번째 이펙트들도 다른블럭과 만나게 되면 다른블럭들은 터질것이다.
	

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
		// 붐블럭이 죽을때는 이펙트 만났을대만이다.
		// 붐블럭이 플레이레벨에서 Destroycheck시 터지는 상황이 없도록 예외 처리 할것!
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
	ATestBullet* BoomEffect = GetWorld()->SpawnActor<ATestBullet>();	
	int col = GetBlockLocationCol();
	int row = 0;
	FVector SetPos = GetBlockFVector(col, row);

	int a = 0;
	BoomEffect->SetActorLocation(SetPos);
	BoomEffect->SetDir(FVector::Down);
}


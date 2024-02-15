#include "Number.h"

ANumber::ANumber()
{
}

ANumber::~ANumber()
{
}


void ANumber::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(20);
	Renderer->SetImage("Big_Number");
	Renderer->SetTransform({ {0,0}, {128, 128} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {128, 128} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {64, 64} });
	Renderer->CreateAnimation("Zero", "Big_Number", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("One", "Big_Number", 1, 1, 0.1f, true);
	Renderer->CreateAnimation("Two", "Big_Number", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("Three", "Big_Number", 3, 3, 0.1f, true);
	Renderer->CreateAnimation("Four", "Big_Number", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("Five", "Big_Number", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("Six", "Big_Number", 6, 6, 0.1f, true);
	Renderer->CreateAnimation("Seven", "Big_Number", 7, 7, 0.1f, true);
	Renderer->CreateAnimation("Eight", "Big_Number", 8, 8, 0.1f, true);
	Renderer->CreateAnimation("Nine", "Big_Number", 9, 9, 0.1f, true);
	Renderer->ChangeAnimation("Zero");


	//Renderer = CreateImageRenderer(20);
	//Renderer->SetImage("Small_Number");
	//Renderer->SetTransform({ {0,0}, {64, 64} });
	//Renderer->SetImageCuttingTransform({ {0,0}, {64, 64} });
	//Renderer->CreateAnimation("Idle", "Small_Number", 0, 10, 0.1f, true);
	//Renderer->ChangeAnimation("Idle");
}

void ANumber::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//switch (NumState)
	//{
	//case ANumber::NumberState::None:
	//	break;
	//case ANumber::NumberState::ZERO:
	//	break;
	//case ANumber::NumberState::ONE:
	//	break;
	//case ANumber::NumberState::TWO:
	//	break;
	//case ANumber::NumberState::THREE:
	//	break;
	//case ANumber::NumberState::FOUR:
	//	break;
	//case ANumber::NumberState::FIVE:
	//	break;
	//case ANumber::NumberState::SIX:
	//	break;
	//case ANumber::NumberState::SEVEN:
	//	break;
	//case ANumber::NumberState::EIGHT:
	//	break;
	//case ANumber::NumberState::NINE:
	//	break;
	//case ANumber::NumberState::end:
	//	break;
	//default:
	//	break;
	//}
}


void ANumber::SetNumber(int _set)
{
	Number = _set;
	if (Number == 0)
	{
		NumState = NumberState::ZERO;
		Renderer->ChangeAnimation("Zero");
	}
	else if (Number == 1)
	{
		NumState = NumberState::ONE;
		Renderer->ChangeAnimation("One");
	}
	else if (Number == 2)
	{
		NumState = NumberState::TWO;
		Renderer->ChangeAnimation("Two");
	}
	else if (Number == 3)
	{
		NumState = NumberState::THREE;
		Renderer->ChangeAnimation("Three");
	}
	else if (Number == 4)
	{
		NumState = NumberState::FOUR;
		Renderer->ChangeAnimation("Four");
	}
	else if (Number == 5)
	{
		NumState = NumberState::FIVE;
		Renderer->ChangeAnimation("Five");
	}
	else if (Number == 6)
	{
		NumState = NumberState::SIX;
		Renderer->ChangeAnimation("Six");
	}
	else if (Number == 7)
	{
		NumState = NumberState::SEVEN;
		Renderer->ChangeAnimation("Seven");
	}
	else if (Number == 8)
	{
		NumState = NumberState::EIGHT;
		Renderer->ChangeAnimation("Eight");
	}
	else if (Number == 9)
	{
		NumState = NumberState::NINE;
		Renderer->ChangeAnimation("Nine");
	}
}

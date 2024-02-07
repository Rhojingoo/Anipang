#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "Title_BackGround.h"
#include "Animal_Block.h"
#include "ACursor_Point.h"
#include "Title_Logo.h"
#include "Title_Button.h"
#include "Title_LogoChick.h"
#include "Title_PointAnimation.h"


UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	Title_BG = SpawnActor<ATitle_BackGround>();
	Cursoor = SpawnActor<ACursor_Pointe>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (Title_BG->Isfinish() == true)
	{
		if (LogoMake == false)
		{
			SpawnActor<ATitle_Logo>();		
			SpawnActor<ATitle_LogoChick>();			
			SpawnActor<ATitle_PointAnimation>();
			UIimage = SpawnActor<ATitle_Button>();			
			LogoMake = true;
		}
	}


	if (LogoMake == true)
	{
		
		FVector Curpos = Cursoor->GetPos();
		UIimage->GetSize();
		float MinX = UIimage->GetPos().X - UIimage->GetSize().X/2;
		float MinY = UIimage->GetPos().Y - UIimage->GetSize().Y/2;
		float MaxX = UIimage->GetPos().X + UIimage->GetSize().X/2;
		float MaxY = UIimage->GetPos().Y + UIimage->GetSize().Y/2;

		if (Curpos.X >= MinX && Curpos.X <= MaxX&& Curpos.Y >= MinY && Curpos.Y <= MaxY)
		{
			Cursoor->UIEnter(true);
		}	
		else
		{
			Cursoor->UIEnter(false);
		}
	}

	if (UEngineInput::IsDown('N'))
	{
		GEngine->ChangeLevel("Play");
	}
}

void UTitleLevel::LevelStart(ULevel* _Level)
{
}

void UTitleLevel::LevelEnd(ULevel* _Level)
{
	
}

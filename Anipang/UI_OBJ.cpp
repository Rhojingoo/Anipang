#include "UI_OBJ.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>

UUI_OBJ::UUI_OBJ()
{
}

UUI_OBJ::~UUI_OBJ()
{
}

void UUI_OBJ::BeginPlay()
{
	AActor::BeginPlay();
}

void UUI_OBJ::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	//FVector Curpos = GetTransform().GetPosition();
	//Pos = RenderCurpos + Curpos;
	//Size = Renderer->GetTransform().GetScale();


	FVector Curpos = Cursor->GetPos();

	float MinX = Pos.X - Size.X / 2;
	float MinY = Pos.Y - Size.Y / 2;
	float MaxX = Pos.X + Size.X / 2;
	float MaxY = Pos.Y + Size.Y / 2;

	if (Curpos.X >= MinX && Curpos.X <= MaxX && Curpos.Y >= MinY && Curpos.Y <= MaxY)
	{
		OnButton = true;
		int a = 0;
		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
			if (ButtonClick == true)
			{
				return;
			}
			else if (ButtonClick == false)
			{
				ButtonClick = true;
			}
		}
	}
	else
	{
		OnButton = false;
		int a = 0;
	}
}

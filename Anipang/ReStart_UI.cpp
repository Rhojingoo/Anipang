#include "ReStart_UI.h"
#include <EngineCore\EngineCore.h>
#include "ScoreManager.h"

AReStart_UI::AReStart_UI()
{
}

AReStart_UI::~AReStart_UI()
{
}

void AReStart_UI::BeginPlay()
{
	UUI_OBJ::BeginPlay();
	Renderer = CreateImageRenderer(10);
	Renderer->SetImage("ReStart_UI");
	Renderer->SetTransform({ {0,0}, {200, 45} });
	Renderer->SetImageCuttingTransform({ {0,0}, {314, 90} });
	Renderer->CreateAnimation("Idle", "ReStart_UI", 0, 0, 1.1f, true);
	Renderer->CreateAnimation("OnButton", "ReStart_UI", 1, 1, 1.1f, true);
	Renderer->CreateAnimation("Click", "ReStart_UI", 1, 2, 0.1f, false);
	Renderer->ChangeAnimation("Idle");
}

void AReStart_UI::Tick(float _DeltaTime)
{
	UUI_OBJ::Tick(_DeltaTime);

	FVector RenderCurpos = Renderer->GetTransform().GetPosition();
	FVector Curpos = GetTransform().GetPosition();
	Pos = RenderCurpos + Curpos;
	Size = Renderer->GetTransform().GetScale();


	switch (UIstate)
	{
	case UUI_OBJ::ButtonState::None:
	{
		if (OnButton == true)
		{
			Renderer->ChangeAnimation("OnButton");
			UIstate = ButtonState::ON_Button;
		}
	}
	break;
	case UUI_OBJ::ButtonState::ON_Button:
	{
		if (OnButton == false)
		{
			Renderer->ChangeAnimation("Idle");
			UIstate = ButtonState::None;
		}
		else if (ButtonClick == true)
		{
			Renderer->ChangeAnimation("Click");
			UIstate = ButtonState::Click;
		}
	}
	break;
	case UUI_OBJ::ButtonState::Click:
	{
		if (Renderer->IsCurAnimationEnd() == true)
		{
			GEngine->ChangeLevel("Play");
			ButtonClick = false;
			Renderer->ChangeAnimation("Idle");
			UIstate = ButtonState::None;
			ScoreManager::ClearScore();
			ScoreManager::SetReStart();
		}
	}
	break;
	case UUI_OBJ::ButtonState::End:
		break;
	default:
		break;
	}

}

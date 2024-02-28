#include "Combo_OBJ.h"
#include <EnginePlatform\EngineInput.h>

ACombo_OBJ::ACombo_OBJ()
{
}

ACombo_OBJ::~ACombo_OBJ()
{
}

void ACombo_OBJ::SetFont()
{	
	Text = std::to_string(combo);
	Time = 1.0f;
	Renderer->SetText("Combo : " + Text);
	RenderON = true;
	RenderOFF = false;
	SetActorLocation({ 240,150 });
	AllRenderersActiveOn();
}

void ACombo_OBJ::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(100);
	Renderer->SetText("Text");
	Renderer->SetTextSize(50);
	Renderer->SetTextColor(Color8Bit::Black, Color8Bit::Orange);
	Renderer->SetTextEffect(1);
	Renderer->TextCneterSwitch();
}

void ACombo_OBJ::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (combo <= 0)
	{
		AllRenderersActiveOff();
	}

	if (RenderON == true)
	{
		Time -= _DeltaTime;
		AddActorLocation({ FVector::Up * Speed * _DeltaTime });

		if (Time <= 0.f)
		{
			if (RenderOFF == false)
			{
				AllRenderersActiveOff();
				RenderOFF = true;
				RenderON = false;
			}
		}
	}

}

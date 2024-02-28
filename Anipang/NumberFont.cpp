#include "NumberFont.h"
#include <EnginePlatform\EngineInput.h>

ANumberFont::ANumberFont()
{
}

ANumberFont::~ANumberFont()
{
}

void ANumberFont::BeginPlay()
{
	AActor::BeginPlay();
	Renderer = CreateImageRenderer(100);
	Renderer->SetText("Text");
	Renderer->SetTextSize(50);
	Renderer->SetTextEffect(1);
	//Renderer->SetTextColor(Color8Bit::Black);
	Renderer->SetTextColor(Color8Bit::Black, Color8Bit::White);
}

void ANumberFont::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress('A'))
	{
		AllRenderersActiveOff();
	}

	if (true == UEngineInput::IsPress('D'))
	{
		AllRenderersActiveOn();
	}
}

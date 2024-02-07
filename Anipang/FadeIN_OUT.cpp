#include "PadeIN_OUT.h"

APadeIN_OUT::APadeIN_OUT()
{
}

APadeIN_OUT::~APadeIN_OUT()
{
}

void APadeIN_OUT::BeginPlay()
{
	{
		// 이미지 한장 랜더
		Renderer = CreateImageRenderer(100);
		Renderer->SetImage("Fadeinout.png");
		SetActorLocation({ 0, 0 });
		Renderer->SetTransform({ {240,400}, {480, 800} });
		Renderer->SetImageCuttingTransform({ {0,0}, {1152, 648} });
	}
}

void APadeIN_OUT::Tick(float _DeltaTime)
{
	
	AlphaTime += _DeltaTime;
	if (1.0f <= AlphaTime)
	{		
		AlphaTime = 0.0f;
	}
	if (false == Dir)
	{
		 CheckAlpha -= AlphaTime*0.15f;
		 Renderer->SetAlpha(CheckAlpha);
			
		 if (CheckAlpha < 0.f)
		 {
			 Dir = true;
		 }
	}	
}

#pragma once
#include <EngineCore\Actor.h>

class APlay_Frame : public AActor
{
public : 
	APlay_Frame();
	~APlay_Frame();

	APlay_Frame(const APlay_Frame& _Other)							 = delete;
	APlay_Frame(APlay_Frame& _Other) noexcept						 = delete;
	APlay_Frame& operator =(const APlay_Frame& _Other)				 = delete;
	APlay_Frame& operator =(APlay_Frame& _Other) noexcept			 = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	UImageRenderer* Renderer = nullptr;
};


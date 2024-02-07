#pragma once
#include <EngineCore\Actor.h>

class APadeIN_OUT : public AActor
{
public:
	APadeIN_OUT();
	~APadeIN_OUT();

	APadeIN_OUT(const APadeIN_OUT& _Other)						= delete;
	APadeIN_OUT(APadeIN_OUT& _Other) noexcept					= delete;
	APadeIN_OUT& operator =(const 	APadeIN_OUT& _Other)		= delete;
	APadeIN_OUT& operator =(APadeIN_OUT& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	float AlphaTime = 0.0f;
	float CheckAlpha = 1.0f;
	bool Dir = false;
};


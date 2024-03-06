#pragma once
#include <EngineCore\Actor.h>

class AManual : public AActor
{
public : 
	AManual();
	~AManual();

	AManual(const AManual& _Other)					 = delete;
	AManual(AManual& _Other) noexcept				 = delete;
	AManual& operator =(const AManual& _Other)		 = delete;
	AManual& operator =(AManual& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
};


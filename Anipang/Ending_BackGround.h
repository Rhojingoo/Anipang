#pragma once
#include <EngineCore\Actor.h>

class AEnding_BackGround  : public AActor
{
public : 
	AEnding_BackGround();
	~AEnding_BackGround();

	AEnding_BackGround(const AEnding_BackGround& _Other)					 = delete;
	AEnding_BackGround(AEnding_BackGround& _Other) noexcept					 = delete;
	AEnding_BackGround& operator =(const AEnding_BackGround& _Other)		 = delete;
	AEnding_BackGround& operator =(AEnding_BackGround& _Other) noexcept		 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	UImageRenderer* Renderer = nullptr;
};


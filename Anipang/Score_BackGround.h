#pragma once
#include <EngineCore\Actor.h>

class AScore_BackGround : public AActor
{
public : 
	AScore_BackGround();
	~AScore_BackGround();

	AScore_BackGround(const AScore_BackGround& _Other)					 = delete;
	AScore_BackGround(AScore_BackGround& _Other) noexcept				 = delete;
	AScore_BackGround& operator =(const AScore_BackGround& _Other)		 = delete;
	AScore_BackGround& operator =(AScore_BackGround& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
};


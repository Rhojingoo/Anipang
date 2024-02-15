#pragma once
#include <EngineCore\Actor.h>


class AScoreBoard : public AActor
{
public : 
	AScoreBoard();
	~AScoreBoard();

	AScoreBoard(const AScoreBoard& _Other)					 = delete;
	AScoreBoard(AScoreBoard& _Other) noexcept				 = delete;
	AScoreBoard& operator =(const AScoreBoard& _Other)		 = delete;
	AScoreBoard& operator =(AScoreBoard& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	UImageRenderer* Renderer = nullptr;

};


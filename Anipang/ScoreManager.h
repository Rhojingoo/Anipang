#pragma once
#include <EngineCore\Actor.h>

class ANumber;
class ScoreManager : public AActor
{
public : 
	ScoreManager();
	~ScoreManager();

	ScoreManager(const ScoreManager& _Other)				 = delete;
	ScoreManager(ScoreManager& _Other) noexcept				 = delete;
	ScoreManager& operator =(const ScoreManager& _Other)	 = delete;
	ScoreManager& operator =(ScoreManager& _Other) noexcept	 = delete;

	void SetScore(int _Score) { Score = _Score; }

protected:
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	int Score = 0;

	ANumber* Units = nullptr;
	ANumber* Tens = nullptr;
	ANumber* Hunders = nullptr;
	ANumber* Thousions = nullptr;
};


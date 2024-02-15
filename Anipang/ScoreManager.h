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

	static void SetScore(int _Score) { Score = _Score; }
	static int GetScore() { return Score; }
	void ScoreLevelON() { ScoreLevel_Use = true; }
	static void ClearScore() { Score = 0;}
	static void SetReStart() { Restart = true; }


protected:
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	bool ScoreLevel_Use					 = false;
	static bool Restart;
	static int Score;
	
	ANumber* Units						 = nullptr;
	ANumber* Tens						 = nullptr;
	ANumber* Hunders					 = nullptr;
	ANumber* Thousions					 = nullptr;
};


#pragma once
#include <EngineCore\Actor.h>


class ScoreRecord
{
public:
	int Num = 0;
	std::string Name = {};
	int Score = 0;

	ScoreRecord(int _num, std::string _name, int _score)
		: Num(_num), Name(_name), Score(_score) {}
};

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
	void Screen_ScoreLevel_On() { Screen_ScoreLevel_Use = true; }
	static void ClearScore() { Score = 0;}
	static void SetReStart() { Restart = true; }

	void SetFont();
	void ScoreImageRender();

protected:
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	bool ScoreLevel_Use					 = false;
	bool Screen_ScoreLevel_Use			 = false;
	static bool Restart;
	static int Score;
	
	ANumber* Units						 = nullptr;
	ANumber* Tens						 = nullptr;
	ANumber* Hunders					 = nullptr;
	ANumber* Thousions					 = nullptr;

	std::string Text = "";
	UImageRenderer* Renderer = nullptr;
};


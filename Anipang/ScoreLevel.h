#pragma once
#include <EngineCore\Level.h>

#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <EngineBase\EngineFile.h>

class ScoreManager;
class ACursor;
class UScoreLevel : public ULevel
{
public : 
	UScoreLevel();
	~UScoreLevel();

	UScoreLevel(const UScoreLevel& _Other)							 = delete;
	UScoreLevel(UScoreLevel& _Other) noexcept						 = delete;
	UScoreLevel& operator =(const UScoreLevel& _Other)				 = delete;
	UScoreLevel& operator =(UScoreLevel& _Other) noexcept			 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:
	ACursor* Cursor					= nullptr;
	ScoreManager* ScoreMN			= nullptr;



	// 스코어 변경 할수 있는 함수
	bool Begin = false;
	std::list<class ScoreRecord*> check_list;
	UEngineFile NewFile;
	std::fstream fs;
	int count = 0;
	void SettingScore();


	void ScoreCheck(int _score);
	bool InputName = false;
	bool ScoreReset = false;

	std::string TextInput;
	class ANumberFont* Input_Font = nullptr;
	class ARecordBoard* RecordBoard = nullptr;
	void ResetScore(int _score);

	void InputCheck();
	bool Input_Text = false;
	int Text_MaxCount = 2;
	int Text_Count = 0;
};


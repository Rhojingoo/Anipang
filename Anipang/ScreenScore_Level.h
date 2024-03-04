#pragma once
#include <EngineCore\Level.h>
#include <EnginePlatform\EngineSound.h>

#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <EngineBase\EngineFile.h>



class ScoreManager;
class ACursor;
class UScreenScore_Level : public ULevel
{
public:
	UScreenScore_Level();
	~UScreenScore_Level();

	UScreenScore_Level(const UScreenScore_Level& _Other)					= delete;
	UScreenScore_Level(UScreenScore_Level& _Other) noexcept					= delete;
	UScreenScore_Level& operator =(const 	UScreenScore_Level& _Other)		= delete;
	UScreenScore_Level& operator =(UScreenScore_Level& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;


private:
	UEngineSoundPlayer Play_Game_Sound;
	ACursor* Cursor = nullptr;
	ScoreManager* ScoreMN = nullptr;


	// 스코어 변경 할수 있는 함수
	bool Begin = false;
	std::list<class ScoreRecord*> check_list;
	UEngineFile NewFile;
	std::fstream fs;
	int count = 0;
	class ANumberFont* font[5] = {};
	void SettingScore();
};


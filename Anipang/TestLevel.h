#pragma once
#include <EngineCore\Level.h>
#include <EnginePlatform\EngineSound.h>


#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <EngineBase\EngineFile.h>

class Scoremanager
{
public:
	int Num = 0;
	std::string Name = {};
	int Score = 0;

	Scoremanager(int _num, std::string _name, int _score)
		: Num(_num), Name(_name), Score(_score) {}
};


class ACursor;
class AAnimal_Block;
class TestLevel : public ULevel
{
public:
	TestLevel();
	~TestLevel();

	TestLevel(const TestLevel& _Other)						= delete;
	TestLevel(TestLevel& _Other) noexcept					= delete;
	TestLevel& operator =(const 	TestLevel& _Other)		= delete;
	TestLevel& operator =(TestLevel& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

	void CreateBlock();
	void AllDestroyCheck();

private:
	UEngineSoundPlayer BGMPlayer;

	ACursor* Cursor						 = nullptr;
	AAnimal_Block* Blocks[7][7]			 = {};
	AAnimal_Block* click_block			 = nullptr;
	AAnimal_Block* swap_block			 = nullptr;

	const int MapSize					 = 7;
	const int TotalBlocks				 = MapSize * MapSize;
	const int CellSize					 = 67;
	const FVector StartLocation			 = { 32, 214 };
	const int CheckBlock				 = 1;
	const float BlockSpeed				 = 300.f;

	bool AllDestroy						 = false;


	// 스코어 변경 할수 있는 함수
	std::list<Scoremanager*> check_list;
	UEngineFile NewFile;
	std::fstream fs;
	int count = 0;
	class ANumberFont* font[5];
};


#pragma once
#include <EngineCore\Level.h>

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
};


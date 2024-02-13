#pragma once
#include <EngineCore\Level.h>

class AAnimal_Block;
class ACursor;
class UPlayLevel : public ULevel
{
public : 
	UPlayLevel();
	~UPlayLevel();

	UPlayLevel(const UPlayLevel& _Other)						 = delete;
	UPlayLevel(UPlayLevel& _Other) noexcept						 = delete;
	UPlayLevel& operator =(const UPlayLevel& _Other)			 = delete;
	UPlayLevel& operator =(UPlayLevel& _Other) noexcept			 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

	void BlockClickUpdate(float _DeltaTime);
	void Blockreturn(int _clickRow, int _clickCol, int _swapkRow, int _swapCol);
	void BlockDestroyCheck();
	void BlockMove();
	void GenerateNewBlocks();
		

	void OBJPOOLTEST();
	void CreateBlock();

private:
	ACursor* Cursoor						= nullptr;
	AAnimal_Block* Blocks[7][7]				= {};
	AAnimal_Block* click_block				= nullptr;
	AAnimal_Block* swap_block				= nullptr;

	const int MapSize						= 7;
	const int TotalBlocks					= MapSize * MapSize;
	const int CellSize						= 67;
	const FVector StartLocation				= { 32, 214 };
	const int CheckBlock					= 1;
};


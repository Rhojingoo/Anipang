#pragma once
#include <EngineCore\Level.h>


class ScoreManager;
class ATime_Gauge;
class AGame_End;
class AGame_Start;
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
	ACursor* Cursor							= nullptr;
	AAnimal_Block* Blocks[7][7]				= {};
	AAnimal_Block* click_block				= nullptr;
	AAnimal_Block* swap_block				= nullptr;
	AGame_Start* Start_Rabbit				= nullptr;
	AGame_End* End_Rabbit					= nullptr;
	ATime_Gauge* Timer						= nullptr;
	ScoreManager* ScoreMN					= nullptr;


	const int MapSize						= 7;
	const int TotalBlocks					= MapSize * MapSize;
	const int CellSize						= 67;
	const FVector StartLocation				= { 32, 214 };
	const int CheckBlock					= 1;

	bool GameStart							= false;
	bool GameEnd							= false;
	int Score								= 0;

	bool XCLICKMOVE							= false;
	bool XSWAPMOVE							= false;
	bool YCLICKMOVE							= false;
	bool YSWAPMOVE							= false;

	const int BlockChangeDefault = 0;
	const int BlockChangeSuccess = 1;
	const int BlockChangeFail = 2;

	int XLINE_ChageCheck = BlockChangeDefault;
	int YLINE_ChageCheck = BlockChangeDefault;
	bool XlinemoveCheck = false;
	bool YlinemoveCheck = false;
	void XlineBlock_Swap_Check(float _DeltaTime);
	void XlineBlock_Swap_Move(float _DeltaTime);
	void YlineBlock_Swap_Check(float _DeltaTime);
	void YlineBlock_Swap_Move(float _DeltaTime);

	FVector Clickpos;
	FVector Swappos;
	FVector TempClick;
	FVector TempSwap;
};


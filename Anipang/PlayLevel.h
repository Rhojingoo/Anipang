#pragma once
#include <EngineCore\Level.h>
#include <List>

class ACombo_OBJ;
class ScoreManager;
class ATime_Gauge;
class AGame_End;
class AGame_Start;
class AAnimal_Block;
class ACursor;
class UPlayLevel : public ULevel
{
public:
	UPlayLevel();
	~UPlayLevel();

	UPlayLevel(const UPlayLevel& _Other) = delete;
	UPlayLevel(UPlayLevel& _Other) noexcept = delete;
	UPlayLevel& operator =(const UPlayLevel& _Other) = delete;
	UPlayLevel& operator =(UPlayLevel& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

	void BlockClickUpdate(float _DeltaTime);
	void Blockreturn(int _clickRow, int _clickCol, int _swapkRow, int _swapCol);
	bool CheckMatchAroundBlock(int col, int row);
	void XlineBlock_Swap_Check(float _DeltaTime);
	void XlineBlock_Swap_Move(float _DeltaTime);
	void YlineBlock_Swap_Check(float _DeltaTime);
	void YlineBlock_Swap_Move(float _DeltaTime);

	void BoombBlock_Destrot_Check();

	void BlockDestroyCheck();
	void BlockMove(float _DeltaTime);
	void GenerateNewBlocks();
	void BlockMoveCheck();


	void OBJPOOLTEST();
	void CreateBlock();

private:
	ACursor* Cursor							 = nullptr;
	AAnimal_Block* Blocks[7][7]				 = {};
	AAnimal_Block* click_block				 = nullptr;
	AAnimal_Block* swap_block				 = nullptr;
	AAnimal_Block* Find_block				 = nullptr;
	AGame_Start* Start_Rabbit				 = nullptr;
	AGame_End* End_Rabbit					 = nullptr;
	ATime_Gauge* Timer						 = nullptr;
	ScoreManager* ScoreMN					 = nullptr;
	ACombo_OBJ* Combo_OBJ					 = nullptr;

	FVector Clickpos						 = {};
	FVector Swappos							 = {};
	FVector TempClick						 = {};
	FVector TempSwap						 = {};

	const int MapSize						 = 7;
	const int TotalBlocks					 = MapSize * MapSize;
	const int CellSize						 = 67;
	const FVector StartLocation				 = { 32, 214 };
	const int CheckBlock					 = 1;
	const float BlockSpeed					 = 300.f;

	bool GameStart							 = false;
	bool GameEnd							 = false;
	int Score								 = 0;

	bool XCLICKMOVE							 = false;
	bool XSWAPMOVE							 = false;
	bool YCLICKMOVE							 = false;
	bool YSWAPMOVE							 = false;

	bool FindBlock							 = false;
	bool CheckMatch							 = true;
	bool CanAMatch							 = false;
	bool ClickChangeCheck					 = false;
	const int BlockChangeDefault			 = 0;
	const int BlockChangeSuccess			 = 1;
	const int BlockChangeFail				 = 2;
	int XLINE_ChageCheck					 = BlockChangeDefault;
	int YLINE_ChageCheck					 = BlockChangeDefault;
	bool XlinemoveCheck						 = false;
	bool YlinemoveCheck						 = false;

	bool BlockDestroyAllow					 = true;

	int Combo								 = 0;
	int PreveCombo							 = 0;
	bool ComboAdd							 = false;
	const int ComboBoombCheck				 = 5;
	bool ComboBomb_Right					 = false;
	bool ComboBomb_Left						 = false;

	bool BoombBlock_Destroy_Start			 = false;
	int ComboTens							 = 0;
	float ComboTime							 = 0.f;
	bool ComboTimeCheck						 = false;
	void ComboCheck(float _DeltaTime);
	void ClearCombotime() { ComboTime = 0.f; }

	bool CanMakeAMatch();
	bool CheckForMatch(int _col, int _row);

	void AllDestroyCheck();
	bool AllDestroy							 = false;


};


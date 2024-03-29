#pragma once
#include <EngineCore\Actor.h>
#include "Block_Location.h"
#include "Cursor.h"
#include <EnginePlatform\EngineSound.h>

class ABlockBoomb_Effect;
class ABombBlock_Effect;
class ABase_Block : public AActor,  public UBlock_Location
{
public:
	struct int2
	{
		int Row;
		int Column;
	};

	enum class Block_Status
	{
		Idle,
		Click,
		Move,
		Bomb,
		Find,
		End,
	};

	enum class Block_Type
	{
		None,
		Cat,
		Checkin,
		Dog,
		Monkey,
		Mouse,
		Pig,
		Rabbit,
		Bomb,
		End,
	};


	ABase_Block();
	~ABase_Block();

	ABase_Block(const ABase_Block& _Other) = delete;
	ABase_Block(ABase_Block& _Other) noexcept = delete;
	ABase_Block& operator =(const ABase_Block& _Other) = delete;
	ABase_Block& operator =(ABase_Block& _Other) noexcept = delete;

	void SetCursor(ACursor* _Cursor) { Cursor = _Cursor; }
	void SetRow(int _Row) { BlockLocation.Row = _Row; }
	void SetColumn(int _Column) { BlockLocation.Column = _Column; }
	int2 GetBlockLocation() { return BlockLocation; }
	int GetBlockLocationRow() { return BlockLocation.Row; }
	int GetBlockLocationCol() { return BlockLocation.Column; }

	static bool GetFirstClick() { return FirstClick; }
	static bool GetSecondClick() { return SecondClick; }
	bool GetFirstPick() { return FirstPick; }
	bool GetSecondPick() { return SecondPick; }

	static bool SwapREADY;
	static bool ClickChange;
	static bool SwapChange;

	void SetBlockstate(bool _Blockstatus, int _set)
	{
		BlockClick = _Blockstatus;
		if (_set == 1)
		{
			FirstClick = BlockClick;
			FirstPick = BlockClick;
		}
		else if (_set == 2)
		{
			SecondClick = BlockClick;
			SecondPick = BlockClick;
		}
	}

	void SetBlockType(int _Set);
	Block_Type GetBlockType() { return Blocktype; }
	Block_Status GetBlockStatus() { return Blockstatus; }

	void SetBoomb(bool _BoombBlock) { BoombBlock = _BoombBlock; }
	bool GetBoomb() { return BoombBlock; }

	void SetUnderBoomb(bool _BoombBlock) { UnderBlockBoomb = _BoombBlock; }
	bool GetUnderBoomb() { return UnderBlockBoomb; }
	void SetUnderPos(FVector _Set) { UnderPos = _Set; }
	FVector GetUnderPos() { return UnderPos; }

	bool Check_Boomb_Effect_Toutch() { return BoombBlock_First_Effect_Toutch; }
	bool Check_Boomb_first_Toutch() { return BoombBlock_First_Toutch; }

	void FindBlock() { LetsFind = true; }
	void FindEndBlock() { LetsFind = false; }
	bool ISFind() { return FindEnd; }



protected:
	UImageRenderer* Renderer					 = nullptr;
	ABlockBoomb_Effect* Block_Destroy_Effect	 = nullptr;
	FVector Pos									 = {};
	FVector UnderPos							 = {};
	FVector Size								 = {};
	bool BlockClick								 = false;
	bool ClickCheck								 = false;
	Block_Status Blockstatus					 = Block_Status::Idle;
	Block_Type Blocktype						 = Block_Type::None;



	static bool FirstClick;
	static bool SecondClick;
	int2 BlockLocation							 = { 0,0 };
	bool FirstPick								 = false;
	bool SecondPick								 = false;
	bool BoombBlock								 = false;
	bool UnderBlockBoomb						 = false;
	float DownSpeed								 = 300.f;
	float FindTime								 = 0.f;
	bool AlphaBlend								 = false;
	bool LetsFind								 = false;
	bool FindEnd								 = false;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CreateBlockEffect();

	static ABombBlock_Effect* BoombBlock_First_Effect;
	static ABombBlock_Effect* BoombBlock_Left_Effect;
	static ABombBlock_Effect* BoombBlock_Right_Effect;
	static ABombBlock_Effect* BoombBlock_Down_Effect;


	static bool BoombBlock_FirstEffect_Create;
	static bool BoombBlock_SecondEffect_Create;

	static FVector BoombBlock_First_Effect_Pos;
	static FVector BoombBlock_Right_Effect_Pos;
	static FVector BoombBlock_Left_Effect_Pos;
	static FVector BoombBlock_Down_Effect_Pos;
	void CheckBoombBlockEffect();
	bool BoombBlock_First_Effect_Toutch				 = false;
	bool BoombBlock_First_Toutch					 = false;



private:
	ACursor* Cursor									 = nullptr;
	void PickingCheck();



};


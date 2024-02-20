#pragma once
#include <EngineCore\Actor.h>
#include "Block_Location.h"
#include "Cursor.h"

class AAnimal_Block : public AActor,  public UBlock_Location
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
		Boomb,
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
		Boomb,
		End,
	};


	AAnimal_Block();
	~AAnimal_Block();

	AAnimal_Block(const AAnimal_Block& _Other) = delete;
	AAnimal_Block(AAnimal_Block& _Other) noexcept = delete;
	AAnimal_Block& operator =(const AAnimal_Block& _Other) = delete;
	AAnimal_Block& operator =(AAnimal_Block& _Other) noexcept = delete;

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

	Block_Type GetBlockType() { return Blocktype; }

	void SetBoomb(bool _BoombBlock) { BoombBlock = _BoombBlock; }
	bool GetBoomb() { return BoombBlock; }

	void SetUnderBoomb(bool _BoombBlock) { UnderBlockBoomb = _BoombBlock; }
	bool GetUnderBoomb() { return UnderBlockBoomb; }
	void SetUnderPos(FVector _Set) { UnderPos = _Set; }
	FVector GetUnderPos() { return UnderPos; }


protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};
	FVector UnderPos = {};
	FVector Size = {};
	bool BlockClick = false;
	bool ClickCheck = false;
	Block_Status Blockstatus = Block_Status::Idle;
	Block_Type Blocktype = Block_Type::None;

	static bool FirstClick;
	static bool SecondClick;
	int2 BlockLocation = { 0,0 };
	bool FirstPick = false;
	bool SecondPick = false;
	bool BoombBlock = false;
	bool UnderBlockBoomb = false;
	float DownSpeed = 300.f;



	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CreateBlockEffect();

private:
	ACursor* Cursor = nullptr;
	void PickingCheck();
};


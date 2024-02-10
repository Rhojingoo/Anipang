#pragma once
#include <EngineCore\Actor.h>
#include "Cursor.h"


class AAnimal_Block : public AActor
{
public : 
	struct int2
	{
		int Row;
		int Column;
	};

	enum class Block_Status
	{
		Idle, 
		Click,
		Boomb,
		End,
	};


	AAnimal_Block();
	~AAnimal_Block();

	AAnimal_Block(const AAnimal_Block& _Other)								= delete;
	AAnimal_Block(AAnimal_Block& _Other) noexcept							= delete;
	AAnimal_Block& operator =(const AAnimal_Block& _Other)					= delete;
	AAnimal_Block& operator =(AAnimal_Block& _Other) noexcept				= delete;

	void SetCursor(ACursor* _Cursor) { Cursor = _Cursor; }
	void SetRow(int _Row) { BlockLocation.Row = _Row; }
	void SetColumn(int _Column) { BlockLocation.Column = _Column; }
	int2 GetBlockLocation() { return BlockLocation; }

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
			FirstClick = _Blockstatus;
			FirstPick = _Blockstatus;
		}
		else if (_set == 2)
		{
			SecondClick = _Blockstatus;
			SecondPick = _Blockstatus;
		}
	}


protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};
	FVector Size = {};
	bool BlockClick = false;
	bool ClickCheck = false;
	Block_Status Blockstatus = Block_Status::Idle;

	static bool FirstClick;
	static bool SecondClick;
	int2 BlockLocation = {0,0};
	bool FirstPick = false;
	bool SecondPick = false;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	ACursor* Cursor = nullptr;
	void PickingCheck();
};


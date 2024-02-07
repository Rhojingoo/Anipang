#pragma once
#include <EngineCore\Actor.h>
#include "Cursor.h"


class AAnimal_Block : public AActor
{
public : 
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

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};
	FVector Size = {};
	bool BlockClick = false;
	bool ClickCheck = false;
	Block_Status Blockstatus = Block_Status::Idle;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	ACursor* Cursor = nullptr;

	void PickingCheck();
};


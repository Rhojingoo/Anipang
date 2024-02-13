#pragma once
#include "Animal_Block.h"

class APig_Block : public AAnimal_Block
{
public:
	APig_Block();
	~APig_Block();

	APig_Block(const APig_Block& _Other)							= delete;
	APig_Block(APig_Block& _Other) noexcept							= delete;
	APig_Block& operator =(const APig_Block& _Other)				= delete;
	APig_Block& operator =(APig_Block& _Other) noexcept				= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

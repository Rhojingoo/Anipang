#pragma once
#include "Base_Block.h"

class AAnimal_Block : public ABase_Block
{
public:
	AAnimal_Block();
	~AAnimal_Block();

	AAnimal_Block(const AAnimal_Block& _Other)					= delete;
	AAnimal_Block(AAnimal_Block& _Other) noexcept					= delete;
	AAnimal_Block& operator =(const 	AAnimal_Block& _Other)		= delete;
	AAnimal_Block& operator =(AAnimal_Block& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool FirstImageSelect = false;
};


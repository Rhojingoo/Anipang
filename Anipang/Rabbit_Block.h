#pragma once
#include "Base_Block.h"

class ARabbit_Block : public ABase_Block
{
public:
	ARabbit_Block();
	~ARabbit_Block();

	ARabbit_Block(const ARabbit_Block& _Other)							= delete;
	ARabbit_Block(ARabbit_Block& _Other) noexcept						= delete;
	ARabbit_Block& operator =(const ARabbit_Block& _Other)				= delete;
	ARabbit_Block& operator =(ARabbit_Block& _Other) noexcept			= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

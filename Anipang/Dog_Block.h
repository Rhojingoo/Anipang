#pragma once
#include "Base_Block.h"

class ADog_Block : public ABase_Block
{
public:
	ADog_Block();
	~ADog_Block();

	ADog_Block(const ADog_Block& _Other)							= delete;
	ADog_Block(ADog_Block& _Other) noexcept							= delete;
	ADog_Block& operator =(const ADog_Block& _Other)				= delete;
	ADog_Block& operator =(ADog_Block& _Other) noexcept				= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

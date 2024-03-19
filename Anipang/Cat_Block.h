#pragma once
#include "Base_Block.h"

class ACat_Block : public ABase_Block
{
public:
	ACat_Block();
	~ACat_Block();

	ACat_Block(const ACat_Block& _Other)									= delete;
	ACat_Block(ACat_Block& _Other) noexcept									= delete;
	ACat_Block& operator =(const ACat_Block& _Other)						= delete;
	ACat_Block& operator =(ACat_Block& _Other) noexcept						= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};


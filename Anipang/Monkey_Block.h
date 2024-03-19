#pragma once
#include "Base_Block.h"

class AMonkey_Block : public ABase_Block
{
public : 
	AMonkey_Block();
	~AMonkey_Block();

	AMonkey_Block(const AMonkey_Block& _Other)					 = delete;
	AMonkey_Block(AMonkey_Block& _Other) noexcept				 = delete;
	AMonkey_Block& operator =(const AMonkey_Block& _Other)		 = delete;
	AMonkey_Block& operator =(AMonkey_Block& _Other) noexcept	 = delete;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
};


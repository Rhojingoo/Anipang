#pragma once
#include "Base_Block.h"


class ABombBlock_Effect;
class ABomb_Block : public ABase_Block
{
public:
	ABomb_Block();
	~ABomb_Block();

	ABomb_Block(const ABomb_Block& _Other)					= delete;
	ABomb_Block(ABomb_Block& _Other) noexcept					= delete;
	ABomb_Block& operator =(const 	ABomb_Block& _Other)		= delete;
	ABomb_Block& operator =(ABomb_Block& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Create_First_Effect();
	void CollCheck_First_Effect();
	void Check_Second_Destroy();

private:
	bool FirstEffect_Create = false;;
};


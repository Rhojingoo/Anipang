#pragma once
#include "Animal_Block.h"


class ABoombBlock_Effect;
class ABoomb_Block : public AAnimal_Block
{
public:
	ABoomb_Block();
	~ABoomb_Block();

	ABoomb_Block(const ABoomb_Block& _Other)					= delete;
	ABoomb_Block(ABoomb_Block& _Other) noexcept					= delete;
	ABoomb_Block& operator =(const 	ABoomb_Block& _Other)		= delete;
	ABoomb_Block& operator =(ABoomb_Block& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Create_First_Effect();
	void CollCheck_First_Effect();
	void Check_Second_Destroy();

private:
	bool FirstEffect_Create = false;;


};


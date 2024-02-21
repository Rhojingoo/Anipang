#pragma once
#include "Animal_Block.h"


class ATestBullet;
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

private:
	bool FirstEffect_Create = false;
	ATestBullet* First_Effect = nullptr;
	FVector First_Effect_Pos = {};

	ATestBullet* Left_Effect = nullptr;
	ATestBullet* Right_Effect = nullptr;
	ATestBullet* Down_Effect = nullptr;
};


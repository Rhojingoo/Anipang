#pragma once
#include "Animal_Block.h"

class ACheckin_Block : public AAnimal_Block
{
public:
	ACheckin_Block();
	~ACheckin_Block();

	ACheckin_Block(const ACheckin_Block& _Other)								= delete;
	ACheckin_Block(ACheckin_Block& _Other) noexcept							= delete;
	ACheckin_Block& operator =(const ACheckin_Block& _Other)					= delete;
	ACheckin_Block& operator =(ACheckin_Block& _Other) noexcept				= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};


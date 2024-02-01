#pragma once
#include "Animal_Block.h"

class ADog_Block : public AAnimal_Block
{
public:
	ADog_Block();
	~ADog_Block();

	ADog_Block(const ADog_Block& _Other)								= delete;
	ADog_Block(ADog_Block& _Other) noexcept							= delete;
	ADog_Block& operator =(const ADog_Block& _Other)					= delete;
	ADog_Block& operator =(ADog_Block& _Other) noexcept				= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};

#pragma once
#include "Animal_Block.h"

class ACat_Block : public AAnimal_Block
{
public:
	ACat_Block();
	~ACat_Block();

	ACat_Block(const ACat_Block& _Other)									= delete;
	ACat_Block(ACat_Block& _Other) noexcept								= delete;
	ACat_Block& operator =(const ACat_Block& _Other)						= delete;
	ACat_Block& operator =(ACat_Block& _Other) noexcept					= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};


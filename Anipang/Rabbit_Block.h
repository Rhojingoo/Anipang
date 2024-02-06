#pragma once
#include "Animal_Block.h"

class ARabbit_Block : public AAnimal_Block
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
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};

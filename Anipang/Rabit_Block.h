#pragma once
#include "Animal_Block.h"

class ARabit_Block : public AAnimal_Block
{
public:
	ARabit_Block();
	~ARabit_Block();

	ARabit_Block(const ARabit_Block& _Other)							= delete;
	ARabit_Block(ARabit_Block& _Other) noexcept						= delete;
	ARabit_Block& operator =(const ARabit_Block& _Other)				= delete;
	ARabit_Block& operator =(ARabit_Block& _Other) noexcept			= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};

#pragma once
#include <EngineCore\Actor.h>

class AAnimal_Block : public AActor
{
public : 
	AAnimal_Block();
	~AAnimal_Block();

	AAnimal_Block(const AAnimal_Block& _Other)								= delete;
	AAnimal_Block(AAnimal_Block& _Other) noexcept							= delete;
	AAnimal_Block& operator =(const AAnimal_Block& _Other)					= delete;
	AAnimal_Block& operator =(AAnimal_Block& _Other) noexcept				= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};


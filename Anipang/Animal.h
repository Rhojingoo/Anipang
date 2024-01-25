#pragma once
#include <EngineCore\Actor.h>

class AAnimal : public AActor
{
public : 
	AAnimal();
	~AAnimal();

	AAnimal(const AAnimal& _Other)					 = delete;
	AAnimal(AAnimal& _Other) noexcept				 = delete;
	AAnimal& operator =(const AAnimal& _Other)		 = delete;
	AAnimal& operator =(AAnimal& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
};


#pragma once
#include <EngineCore\Actor.h>

class ACursor_Pointe : public AActor
{
public:
	ACursor_Pointe();
	~ACursor_Pointe();

	ACursor_Pointe(const ACursor_Pointe& _Other)							= delete;
	ACursor_Pointe(ACursor_Pointe& _Other) noexcept							= delete;
	ACursor_Pointe& operator =(const ACursor_Pointe& _Other)				= delete;
	ACursor_Pointe& operator =(ACursor_Pointe& _Other) noexcept				= delete;

protected:
	void BeginPlay() override; 
		void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};


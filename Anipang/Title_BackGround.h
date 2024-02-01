#pragma once
#include <EngineCore\Actor.h>

class ATitle_BackGround : public AActor
{
public:
	ATitle_BackGround();
	~ATitle_BackGround();

	ATitle_BackGround(const ATitle_BackGround& _Other)						= delete;
	ATitle_BackGround(ATitle_BackGround& _Other) noexcept					= delete;
	ATitle_BackGround& operator =(const ATitle_BackGround& _Other)			= delete;
	ATitle_BackGround& operator =(ATitle_BackGround& _Other) noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float QSkillCool = 0.0f;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
};


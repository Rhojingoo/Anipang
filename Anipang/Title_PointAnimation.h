#pragma once
#include <EngineCore\Actor.h>

class ATitle_PointAnimation : public AActor
{

public:
	ATitle_PointAnimation();
	~ATitle_PointAnimation();

	ATitle_PointAnimation(const ATitle_PointAnimation& _Other)					= delete;
	ATitle_PointAnimation(ATitle_PointAnimation& _Other) noexcept					= delete;
	ATitle_PointAnimation& operator =(const 	ATitle_PointAnimation& _Other)		= delete;
	ATitle_PointAnimation& operator =(ATitle_PointAnimation& _Other)noexcept		= delete;

	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
};


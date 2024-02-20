#pragma once
#include <EngineCore\Actor.h>

class ATestBullet : public AActor
{
public : 
	ATestBullet();
	~ATestBullet();

	ATestBullet(const ATestBullet& _Other)								 = delete;
	ATestBullet(ATestBullet& _Other) noexcept							 = delete;
	ATestBullet& operator =(const ATestBullet& _Other)					 = delete;
	ATestBullet& operator =(ATestBullet& _Other) noexcept				 = delete;


	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	FVector Dir = FVector::Zero;
	const float Speed = 250.0f;
};


#pragma once
#include <EngineCore\Actor.h>

class TestBullet : public AActor
{
public : 
	TestBullet();
	~TestBullet();

	TestBullet(const TestBullet& _Other)								 = delete;
	TestBullet(TestBullet& _Other) noexcept								 = delete;
	TestBullet& operator =(const TestBullet& _Other)					 = delete;
	TestBullet& operator =(TestBullet& _Other) noexcept					 = delete;


	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
};


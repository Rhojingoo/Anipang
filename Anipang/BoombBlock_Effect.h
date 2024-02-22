#pragma once
#include <EngineCore\Actor.h>

class ABoombBlock_Effect : public AActor
{
public : 
	ABoombBlock_Effect();
	~ABoombBlock_Effect();

	ABoombBlock_Effect(const ABoombBlock_Effect& _Other)								 = delete;
	ABoombBlock_Effect(ABoombBlock_Effect& _Other) noexcept							 = delete;
	ABoombBlock_Effect& operator =(const ABoombBlock_Effect& _Other)					 = delete;
	ABoombBlock_Effect& operator =(ABoombBlock_Effect& _Other) noexcept				 = delete;


	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}
	void SetSideReder() { SideRender = true; }
	bool IsSecondEffectDEATH() { return Death; }

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* DirRenderer = nullptr;
	FVector Dir = FVector::Zero;
	const float Speed = 250.0f;
	bool SideRender = false;
	float DeathTimeCheck = 5.0f;
	bool DeathTimeStart = false;
	bool Death = false;
};


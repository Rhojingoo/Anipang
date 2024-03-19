#pragma once
#include <EngineCore\Actor.h>

class ABombBlock_Effect : public AActor
{
public : 
	ABombBlock_Effect();
	~ABombBlock_Effect();

	ABombBlock_Effect(const ABombBlock_Effect& _Other)							 = delete;
	ABombBlock_Effect(ABombBlock_Effect& _Other) noexcept							 = delete;
	ABombBlock_Effect& operator =(const ABombBlock_Effect& _Other)				 = delete;
	ABombBlock_Effect& operator =(ABombBlock_Effect& _Other) noexcept				 = delete;


	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;

		if (Dir.X == -1.0f)
		{
			float Angle = 90.0f;
			Renderer->SetAngle(Angle);
			Destroy(5.f);
		}
		else if (Dir.X == 1.0f)
		{
			float Angle = -90.0f;
			Renderer->SetAngle(Angle);
			Destroy(5.f);
		}
	}
	void SetSideReder() { SideRender = true; }
	bool IsSecondEffectDEATH() { return Death; }

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	UImageRenderer* Renderer = nullptr;
	FVector Dir = FVector::Zero;
	const float Speed = 250.0f;
	bool SideRender = false;
	float DeathTimeCheck = 5.0f;
	bool DeathTimeStart = false;
	bool Death = false;
};


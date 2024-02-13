#pragma once
#include <EngineCore\Actor.h>

class ABlockBoomb_Effect : public AActor
{
public:
	ABlockBoomb_Effect();
	~ABlockBoomb_Effect();

	ABlockBoomb_Effect(const ABlockBoomb_Effect& _Other)					= delete;
	ABlockBoomb_Effect(ABlockBoomb_Effect& _Other) noexcept					= delete;
	ABlockBoomb_Effect& operator =(const 	ABlockBoomb_Effect& _Other)		= delete;
	ABlockBoomb_Effect& operator =(ABlockBoomb_Effect& _Other)noexcept		= delete;


protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};


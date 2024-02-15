#pragma once
#include <EngineCore\Actor.h>


class ABoomb_Block_Effect : public AActor
{
public:
	ABoomb_Block_Effect();
	~ABoomb_Block_Effect();

	ABoomb_Block_Effect(const ABoomb_Block_Effect& _Other)						= delete;
	ABoomb_Block_Effect(ABoomb_Block_Effect& _Other) noexcept					= delete;
	ABoomb_Block_Effect& operator =(const 	ABoomb_Block_Effect& _Other)		= delete;
	ABoomb_Block_Effect& operator =(ABoomb_Block_Effect& _Other)noexcept		= delete;

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};
	int Destroycheck = 0;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
};


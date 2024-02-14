#pragma once
#include <EngineCore\Actor.h>

class ANumber : public AActor
{
public:
	ANumber();
	~ANumber();

	ANumber(const ANumber& _Other)					= delete;
	ANumber(ANumber& _Other) noexcept					= delete;
	ANumber& operator =(const 	ANumber& _Other)		= delete;
	ANumber& operator =(ANumber& _Other)noexcept		= delete;


protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:


};


#pragma once
#include <EngineCore\Actor.h>

class AGame_End : public AActor
{
public : 
	AGame_End();
	~AGame_End();

	AGame_End(const AGame_End& _Other)					 = delete;
	AGame_End(AGame_End& _Other) noexcept				 = delete;
	AGame_End& operator =(const AGame_End& _Other)		 = delete;
	AGame_End& operator =(AGame_End& _Other) noexcept	 = delete;

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
};


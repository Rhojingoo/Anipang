#pragma once
#include <EngineCore\Actor.h>

class AGame_Start : public AActor
{
public : 
	AGame_Start();
	~AGame_Start();

	AGame_Start(const AGame_Start& _Other)					 = delete;
	AGame_Start(AGame_Start& _Other) noexcept				 = delete;
	AGame_Start& operator =(const AGame_Start& _Other)		 = delete;
	AGame_Start& operator =(AGame_Start& _Other) noexcept	 = delete;

	bool IsStart() { return Start; }

protected:
	UImageRenderer* Renderer = nullptr;
	FVector Pos = {};

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	bool Start = false;
};


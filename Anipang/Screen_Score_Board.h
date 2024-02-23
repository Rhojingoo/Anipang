#pragma once
#include <EngineCore\Actor.h>


class AScreen_Score_Board : public AActor
{
public : 
	AScreen_Score_Board();
	~AScreen_Score_Board();

	AScreen_Score_Board(const AScreen_Score_Board& _Other)						 = delete;
	AScreen_Score_Board(AScreen_Score_Board& _Other) noexcept						 = delete;
	AScreen_Score_Board& operator =(const AScreen_Score_Board& _Other)			 = delete;
	AScreen_Score_Board& operator =(AScreen_Score_Board& _Other) noexcept			 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
};


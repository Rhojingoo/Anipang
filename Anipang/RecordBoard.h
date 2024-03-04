#pragma once
#include <EngineCore\Actor.h>


class ARecordBoard : public AActor
{
public : 
	ARecordBoard();
	~ARecordBoard();

	ARecordBoard(const ARecordBoard& _Other)					 = delete;
	ARecordBoard(ARecordBoard& _Other) noexcept					 = delete;
	ARecordBoard& operator =(const ARecordBoard& _Other)		 = delete;
	ARecordBoard& operator =(ARecordBoard& _Other) noexcept		 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
};


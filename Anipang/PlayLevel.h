#pragma once
#include <EngineCore\Level.h>

class UPlayLevel : public ULevel
{
public : 
	UPlayLevel();
	~UPlayLevel();

	UPlayLevel(const UPlayLevel& _Other)						 = delete;
	UPlayLevel(UPlayLevel& _Other) noexcept						 = delete;
	UPlayLevel& operator =(const UPlayLevel& _Other)			 = delete;
	UPlayLevel& operator =(UPlayLevel& _Other) noexcept			 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:
};


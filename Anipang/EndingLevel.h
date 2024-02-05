#pragma once
#include <EngineCore\Level.h>


class UEndingLevel : public ULevel
{
public : 
	UEndingLevel();
	~UEndingLevel();

	UEndingLevel(const UEndingLevel& _Other)						 = delete;
	UEndingLevel(UEndingLevel& _Other) noexcept						 = delete;
	UEndingLevel& operator =(const UEndingLevel& _Other)			 = delete;
	UEndingLevel& operator =(UEndingLevel& _Other) noexcept			 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:


};


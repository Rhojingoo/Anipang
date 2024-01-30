#pragma once
#include <EngineCore\Level.h>

class UScoreLevel : public ULevel
{
public : 
	UScoreLevel();
	~UScoreLevel();

	UScoreLevel(const UScoreLevel& _Other)							 = delete;
	UScoreLevel(UScoreLevel& _Other) noexcept						 = delete;
	UScoreLevel& operator =(const UScoreLevel& _Other)				 = delete;
	UScoreLevel& operator =(UScoreLevel& _Other) noexcept			 = delete;

protected:

private:
};


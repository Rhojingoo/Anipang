#pragma once
#include <EngineCore\Level.h>

class ScoreLevel : public ULevel
{
public : 
	ScoreLevel();
	~ScoreLevel();

	ScoreLevel(const ScoreLevel& _Other)				 = delete;
	ScoreLevel(ScoreLevel& _Other) noexcept				 = delete;
	ScoreLevel& operator =(const ScoreLevel& _Other)	 = delete;
	ScoreLevel& operator =(ScoreLevel& _Other) noexcept	 = delete;

protected:

private:
};


#pragma once
#include <EngineCore\Level.h>

class PlayLevel : public ULevel
{
public : 
	PlayLevel();
	~PlayLevel();

	PlayLevel(const PlayLevel& _Other)					 = delete;
	PlayLevel(PlayLevel& _Other) noexcept				 = delete;
	PlayLevel& operator =(const PlayLevel& _Other)		 = delete;
	PlayLevel& operator =(PlayLevel& _Other) noexcept	 = delete;

protected:

private:
};


#pragma once
#include <EngineCore\Level.h>

class ATitle_Button;
class ACursor_Pointe;
class ATitle_BackGround;
class UTitleLevel : public ULevel
{
public : 
	UTitleLevel();
	~UTitleLevel();

	UTitleLevel(const UTitleLevel& _Other)							 = delete;
	UTitleLevel(UTitleLevel& _Other) noexcept						 = delete;
	UTitleLevel& operator =(const UTitleLevel& _Other)				 = delete;
	UTitleLevel& operator =(UTitleLevel& _Other) noexcept			 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:
	ATitle_BackGround* Title_BG;
	bool LogoMake = false;
	ACursor_Pointe* Cursoor = nullptr;
	ATitle_Button* UIimage = nullptr;
};


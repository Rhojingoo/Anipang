#pragma once
#include <EngineCore\Level.h>
#include <EnginePlatform\EngineSound.h>

class ACursor;
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
	UEngineSoundPlayer BGMPlayer;
	ATitle_BackGround* Title_BG			 = nullptr;
	bool LogoMake						 = false;
	ACursor* Cursor						 = nullptr;
	bool SoundSwitch					 = false;

};


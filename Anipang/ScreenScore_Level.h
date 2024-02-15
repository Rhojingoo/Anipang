#pragma once
#include <EngineCore\Level.h>

class ScoreManager;
class ACursor;
class UScreenScore_Level : public ULevel
{
public:
	UScreenScore_Level();
	~UScreenScore_Level();

	UScreenScore_Level(const UScreenScore_Level& _Other)					= delete;
	UScreenScore_Level(UScreenScore_Level& _Other) noexcept					= delete;
	UScreenScore_Level& operator =(const 	UScreenScore_Level& _Other)		= delete;
	UScreenScore_Level& operator =(UScreenScore_Level& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;


private:
	ACursor* Cursor = nullptr;
	ScoreManager* ScoreMN = nullptr;
};


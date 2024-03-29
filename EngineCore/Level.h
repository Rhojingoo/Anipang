#pragma once
#include <EngineBase\NameObject.h>
#include <EngineBase\EngineMath.h>
#include <map>
#include <list>


//씬을 만들곳
class AActor;
class UCollision;
class UEngineCore;
class UImageRenderer;
class ULevel : public UNameObject
{
	friend UEngineCore;
	friend UImageRenderer;
	friend UCollision;

public : 
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other)						 = delete;
	ULevel(ULevel& _Other) noexcept						 = delete;
	ULevel& operator =(const 	ULevel& _Other)			 = delete;
	ULevel& operator =(ULevel& _Other)noexcept			 = delete;

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

	virtual void LevelStart(ULevel* _PrevLevel) {};
	virtual void LevelEnd(ULevel* _NextLevel) {};

	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

	template<typename ActorType, typename EnumType>
	ActorType* SpawnActor(EnumType _Order)
	{
		return SpawnActor<ActorType>(static_cast<int>(_Order));
	}

	void SetCameraPos(FVector _CameraPos)
	{
		CameraPos = _CameraPos;
	}


	void AddCameraPos(FVector _CameraPos)
	{
		CameraPos += _CameraPos;
	}

	FVector GetCameraPos()
	{
		return CameraPos;
	}

	void SetAllTimeScale(float _Scale)
	{
		for (std::pair<const int, float>& TimeScale : TimeScale)
		{
			TimeScale.second = _Scale;
		}
	}

	// 이거는 기존의 타임스케일이 존재 해야만 가능하다.
	template<typename EnumType>
	void SetOtherTimeScale(EnumType _Value, float _Scale)
	{
		SetOtherTimeScale(static_cast<int>(_Value), _Scale);
	}

	void SetOtherTimeScale(int _Value, float _Scale)
	{
		for (std::pair<const int, float>& TimeScale : TimeScale)
		{
			if (TimeScale.first == _Value)
			{
				continue;
			}

			TimeScale.second = _Scale;
		}
	}

	template<typename EnumType>
	void SetTimeScale(EnumType _Value, float _Scale)
	{
		SetTimeScale(static_cast<int>(_Value), _Scale);
	}

	void SetTimeScale(int _Value, float _Scale)
	{
		TimeScale[_Value] = _Scale;
	}

	virtual void End() {}

protected:

private:
	std::map<int, std::list<AActor*>> AllActor;
	std::map<int, std::list<UImageRenderer*>> Renderers;
	std::map<int, std::list<UCollision*>> Collisions;
	std::map<int, float> TimeScale;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);





	FVector CameraPos = FVector::Zero;
};


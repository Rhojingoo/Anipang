#pragma once
#include <EngineBase\NameObject.h>
#include <EngineBase\EngineMath.h>
#include <map>
#include <list>


//¾ÀÀ» ¸¸µé°÷
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


	//template<typename ActorType>
	//ActorType* SpawnActor(ActorType* _Ac, int _Order = 0)
	//{
	//	ActorType* NewActor = _Ac;
	//	ActorInit(NewActor);
	//	AllActor[_Order].push_back(NewActor);
	//	return NewActor;
	//}

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

protected:

private:
	std::map<int, std::list<AActor*>> AllActor;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);
	std::map<int, std::list<UImageRenderer*>> Renderers;
	std::map<int, std::list<UCollision*>> Collisions;

	FVector CameraPos = FVector::Zero;
};


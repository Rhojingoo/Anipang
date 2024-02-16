#include "Level.h"
#include "Actor.h"
#include <EngineBase\EngineDebug.h>
#include "EngineCore.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (nullptr == Actor)
			{
				continue;
			}

			delete Actor;
			Actor = nullptr;
		}
	}
	AllActor.clear();
}

void ULevel::ActorInit(AActor* _NewActor)
{	
	_NewActor->SetWorld(this);
	_NewActor->BeginPlay();
}

void ULevel::LevelTick(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			Actor->ActiveUpdate(_DeltaTime);
			Actor->DestroyUpdate(_DeltaTime);

			if (false == Actor->IsActive())
			{
				continue;
			}		
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::LevelRender(float _DeltaTime)
{
	for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
	{
		std::list<UImageRenderer*>& RendererList = OrderListPair.second;
		for (UImageRenderer* Renderer : RendererList)
		{
			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->Render(_DeltaTime);
		}
	}

	if (true == GEngine->IsDebug())
	{
		for (std::pair<const int, std::list<UCollision*>>& OrderListPair : Collisions)
		{
			std::list<UCollision*>& RendererList = OrderListPair.second;
			for (UCollision* Collision : RendererList)
			{
				if (false == Collision->IsActive())
				{
					continue;
				}

				Collision->DebugRender(CameraPos);
			}
		}
	}
}

void ULevel::LevelRelease(float _DeltaTime)
{
	{
		for (std::pair<const int, std::list<UCollision*>>& OrderListPair : Collisions)
		{
			std::list<UCollision*>& List = OrderListPair.second;

			std::list<UCollision*>::iterator StartIter = List.begin();
			std::list<UCollision*>::iterator EndIter = List.end();

			for (; StartIter != EndIter; )
			{
				UCollision* Collision = StartIter.operator*();

				if (false == Collision->IsDestroy())
				{				
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}


	{
		for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
		{
			std::list<UImageRenderer*>& List = OrderListPair.second;

			std::list<UImageRenderer*>::iterator StartIter = List.begin();
			std::list<UImageRenderer*>::iterator EndIter = List.end();

			for (; StartIter != EndIter; )
			{
				UImageRenderer* Renderer = StartIter.operator*();

				if (false == Renderer->IsDestroy())
				{
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}

	
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;

		std::list<AActor*>::iterator StartIter = ActorList.begin();
		std::list<AActor*>::iterator EndIter = ActorList.end();

		for (; StartIter != EndIter;)
		{
			AActor* Actor = StartIter.operator*();

			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor가 nullptr인 경우가 존재했습니다");
				return;
			}

			if (false == Actor->IsDestroy())
			{
				Actor->CheckReleaseChild();
				++StartIter;
				continue;
			}

			delete Actor;
			Actor = nullptr;
			StartIter = ActorList.erase(StartIter);
		}
	}
}

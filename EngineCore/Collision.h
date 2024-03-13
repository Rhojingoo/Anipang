#pragma once
#include "SceneComponent.h"
#include <vector>

class UCollision : public USceneComponent
{
public : 
	UCollision();
	~UCollision();

	UCollision(const UCollision& _Other)				 = delete;
	UCollision(UCollision& _Other) noexcept				 = delete;
	UCollision& operator =(const UCollision& _Other)	 = delete;
	UCollision& operator =(UCollision& _Other) noexcept	 = delete;

	void SetOrder(int _Order) override;

	template<typename EnumType>
	bool CollisionCheck(EnumType _Order, std::vector<UCollision*>& _Resul, FVector _NextPos = FVector::Zero)
	{
		return CollisionCheck(static_cast<int>(_Order), _NextPos);
	}

	void SetColType(ECollisionType _Type)
	{
		ColType = _Type;
	}

	bool CollisionCheck(int _Order, std::vector<UCollision*>& _Result, FVector _NextPos = FVector::Zero);
	void DebugRender(FVector _CameraPos);

protected:
	void BeginPlay() override;

private:
	ECollisionType ColType = ECollisionType::Rect;
};


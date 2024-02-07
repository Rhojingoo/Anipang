#pragma once

class PickingManager
{
public:
	PickingManager();
	~PickingManager();

	PickingManager(const PickingManager& _Other)					= delete;
	PickingManager(PickingManager& _Other) noexcept					= delete;
	PickingManager& operator =(const 	PickingManager& _Other)		= delete;
	PickingManager& operator =(PickingManager& _Other)noexcept		= delete;


protected:

private:
};


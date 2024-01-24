#pragma once



struct float4
{
public:
	float X; // 2D
	float Y; // 2D
	float Z;
	float W;

public:
	float hX()
	{
		return X * 0.5f;
	}

	float hY()
	{
		return Y * 0.5f;
	}


	int ihY()
	{
		return static_cast<int>(hY());
	}

	int ihX()
	{
		return static_cast<int>(hX());
	}

};
using FVector = float4;

class EngineMath
{
public : 
	EngineMath();
	~EngineMath();

	EngineMath(const EngineMath& _Other)				 = delete;
	EngineMath(EngineMath& _Other) noexcept				 = delete;
	EngineMath& operator =(const EngineMath& _Other)	 = delete;
	EngineMath& operator =(EngineMath& _Other) noexcept	 = delete;

protected:

private:
};


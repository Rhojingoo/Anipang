#pragma once


class Jewel
{
public : 
	Jewel();
	~Jewel();

	Jewel(const Jewel& _Other) = delete;
	Jewel(Jewel& _Other) noexcept = delete;
	Jewel& operator =(const 	Jewel& _Other) = delete;
	Jewel& operator =(Jewel& _Other)noexcept = delete;

protected:

private:
};


#pragma once


class BackGround
{
public : 
	BackGround();
	~BackGround();

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround& _Other) noexcept = delete;
	BackGround& operator =(const 	BackGround& _Other) = delete;
	BackGround& operator =(BackGround& _Other)noexcept = delete;

protected:

private:
};


#pragma once
#include "Animal_Block.h"
#include <vector>
#include <map>

class ACat_Block;
class ACheckin_Block;
class ADog_Block;
class AMonkey_Block;
class AMouse_Block;
class APig_Block;
class ARabbit_Block;
class Block_Manager
{
public : 
	enum class eBlock
	{
		Cat_Block,
		Checkin_Block,
		Dog_Block,
		Monkey_Block,
		Mouse_Block,
		Pig_Block,
		Rabbit_Block,
		END
	};

	~Block_Manager();
	static Block_Manager* OBJPOOL;
	static Block_Manager& GetInstance()
	{
		static Block_Manager instance;
		return instance;
	}

	Block_Manager(const Block_Manager& _Other)					 = delete;
	Block_Manager(Block_Manager& _Other) noexcept				 = delete;
	Block_Manager& operator =(const Block_Manager& _Other)		 = delete;
	Block_Manager& operator =(Block_Manager& _Other) noexcept	 = delete;

	void BeginPlay();

	AAnimal_Block* GetNextAnimalBlock(eBlock blockType)
	{
		// �ʿ��� �ش� ������ ���͸� ������
		std::vector<AAnimal_Block*>& blockVector = Blocks[blockType];

		// ���Ϳ��� �� ���� ���� ����� ������
		if (!blockVector.empty())
		{
			AAnimal_Block* block = blockVector.back(); // ������ ������ ��� ������
			blockVector.pop_back(); // ���Ϳ��� ������ ��� ����

			switch (blockType)
			{
			case eBlock::Cat_Block:
				--CatBlock_Count;
				break;

			case eBlock::Checkin_Block:
				--CheckinBlock_Count;
				break;

			case eBlock::Dog_Block:
				--DogBlock_Count;
				break;

			case eBlock::Monkey_Block:
				--MonkeyBlock_Count;
				break;

			case eBlock::Mouse_Block:
				--MouseBlock_Count;
				break;

			case eBlock::Pig_Block:
				--PigBlock_Count;
				break;

			case eBlock::Rabbit_Block:
				--RabbitBlock_Count;
				break;

			default:
				break;
			}
			return block; // ���� ��� ��ȯ
		}

		// ���� ���Ͱ� ����ִٸ� nullptr ��ȯ
		return nullptr;
	}

protected:
	void CreateAnimalBlock(int count, eBlock blockType);

private:
	Block_Manager();
	std::map<eBlock, std::vector<AAnimal_Block*>>			Blocks;


	const int MaxBlock		= 15;
	const int MinBlock		= 0;
	int CatBlock_Count		= 0;
	int CheckinBlock_Count	= 0;
	int DogBlock_Count		= 0;
	int MonkeyBlock_Count	= 0;
	int MouseBlock_Count	= 0;
	int PigBlock_Count		= 0;
	int RabbitBlock_Count	= 0;
};






//public:
//std::map<eBlock, AAnimal_Block*> GetCatBlock();
//std::map<eBlock, AAnimal_Block*> GetCheckinBlock();
//std::map<eBlock, AAnimal_Block*> GetDogBlock();
//std::map<eBlock, AAnimal_Block*> GetMonkeyBlock();
//std::map<eBlock, AAnimal_Block*> GetMouseBlock();
//std::map<eBlock, AAnimal_Block*> GetPigBlock();
//std::map<eBlock, AAnimal_Block*> GetRabbtBlock();
//private:
//AAnimal_Block								Blocks[105];	
//std::vector< ACat_Block>					CatBlocks;
//std::vector< ACheckin_Block>				CheckinBlocks;
//std::vector< ADog_Block>					DogBlocks;
//std::vector< AMonkey_Block>				MonkeyBlocks;
//std::vector< AMouse_Block>				MouseBlocks;
//std::vector< APig_Block>					PigBlocks;
//std::vector< ARabbit_Block>				RabbitBlocks;



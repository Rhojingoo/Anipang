#include "Block_Manager.h"
#include "Cat_Block.h"
#include "Dog_Block.h"
#include "Checkin_Block.h"
#include "Mouse_Block.h"
#include "Pig_Block.h"
#include "Rabbit_Block.h"
#include "Monkey_Block.h"

Block_Manager* Block_Manager::OBJPOOL = nullptr;

Block_Manager::Block_Manager()
{
}

Block_Manager::~Block_Manager()
{
	for (auto& blockPair : Blocks)
	{
		std::vector<ABase_Block*>& blockVector = blockPair.second;
		for (ABase_Block* block : blockVector)
		{
			delete block;
		}
	}
}


void Block_Manager::BeginPlay()
{
	CreateAnimalBlock(MaxBlock, eBlock::Cat_Block);
	CreateAnimalBlock(MaxBlock, eBlock::Checkin_Block);
	CreateAnimalBlock(MaxBlock, eBlock::Dog_Block);
	CreateAnimalBlock(MaxBlock, eBlock::Monkey_Block);
	CreateAnimalBlock(MaxBlock, eBlock::Mouse_Block);
	CreateAnimalBlock(MaxBlock, eBlock::Pig_Block);
	CreateAnimalBlock(MaxBlock, eBlock::Rabbit_Block);
}


void Block_Manager::CreateAnimalBlock(int count, eBlock blockType)
{
	std::vector<ABase_Block*> blockVector;
	blockVector.resize(20);

	for (int i = 0; i < count; ++i)
	{
		ABase_Block* NewBlock = nullptr;
		switch (blockType)
		{
		case eBlock::Cat_Block:
			NewBlock = new ACat_Block();
			++CatBlock_Count;
			break;

		case eBlock::Checkin_Block:
			NewBlock = new ACheckin_Block();
			++CheckinBlock_Count;
			break;

		case eBlock::Dog_Block:
			NewBlock = new ADog_Block();
			++DogBlock_Count;
			break;

		case eBlock::Monkey_Block:
			NewBlock = new AMonkey_Block();
			++MonkeyBlock_Count;
			break;

		case eBlock::Mouse_Block:
			NewBlock = new AMouse_Block();
			++MouseBlock_Count;
			break;

		case eBlock::Pig_Block:
			NewBlock = new APig_Block();
			++PigBlock_Count;
			break;

		case eBlock::Rabbit_Block:
			NewBlock = new ARabbit_Block();
			++RabbitBlock_Count;
			break;

		default:
			break;
		}
		if (NewBlock != nullptr)
		{
			NewBlock->SetActive(false);
			blockVector.push_back(NewBlock);
		}
	}
	Blocks[blockType] = blockVector;
}

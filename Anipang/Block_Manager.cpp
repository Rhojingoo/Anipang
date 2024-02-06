#include "Block_Manager.h"
#include "Cat_Block.h"
#include "Dog_Block.h"
#include "Checkin_Block.h"
#include "Mouse_Block.h"
#include "Pig_Block.h"
#include "Rabbit_Block.h"
#include "Monkey_Block.h"



Block_Manager::Block_Manager()
{
}

Block_Manager::~Block_Manager()
{
}

void Block_Manager::BeginPlay()
{
	for (int count = 0; count < MaxBlock; count++)
	{
		ACat_Block* NewBlock = new ACat_Block();
		eBlock Block = eBlock::Cat_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}

	for (int count = 0; count < MaxBlock; count++)
	{
		ADog_Block* NewBlock = new ADog_Block();
		eBlock Block = eBlock::Dog_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}

	for (int count = 0; count < MaxBlock; count++)
	{
		ACheckin_Block* NewBlock = new ACheckin_Block();
		eBlock Block = eBlock::Checkin_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}

	for (int count = 0; count < MaxBlock; count++)
	{
		AMouse_Block* NewBlock = new AMouse_Block();
		eBlock Block = eBlock::Mouse_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}

	for (int count = 0; count < MaxBlock; count++)
	{
		APig_Block* NewBlock = new APig_Block();
		eBlock Block = eBlock::Pig_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}

	for (int count = 0; count < MaxBlock; count++)
	{
		ARabbit_Block* NewBlock = new ARabbit_Block();
		eBlock Block = eBlock::Rabbit_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}

	for (int count = 0; count < MaxBlock; count++)
	{
		AMonkey_Block* NewBlock = new AMonkey_Block();
		eBlock Block = eBlock::Monkey_Block;
		NewBlock->SetActive(false);
		Blocks.insert(std::pair<eBlock, AAnimal_Block* >(Block, NewBlock));
	}
}

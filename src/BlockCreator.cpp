#include "BlockCreator.hpp"
#include "Block1.hpp"
#include "Block2.hpp"
#include "Block3.hpp"
#include "Block4.hpp"
#include "Block5.hpp"
#include "Block6.hpp"
#include "Block7.hpp"

std::unique_ptr<BaseBlock> BlockCreator::createRandomBlock(BlockBoard& blockBoardRef_, std::random_device& rd) noexcept
{
	std::unique_ptr<BaseBlock> createdBlock;
	uint8_t randomNumber;

	std::mt19937 rng(rd());
	std::uniform_int_distribution<> distrib1(0, 6);
	randomNumber = distrib1(rng);
	switch (randomNumber)
	{
	case 0:
		createdBlock = std::make_unique<Block1>(blockBoardRef_);
		break;
	case 1:
		createdBlock = std::make_unique<Block2>(blockBoardRef_);
		break;
	case 2:
		createdBlock = std::make_unique<Block3>(blockBoardRef_);
		break;
	case 3:
		createdBlock = std::make_unique<Block4>(blockBoardRef_);
		break;
	case 4:
		createdBlock = std::make_unique<Block5>(blockBoardRef_);
		break;
	case 5:
		createdBlock = std::make_unique<Block6>(blockBoardRef_);
		break;
	case 6:
		createdBlock = std::make_unique<Block7>(blockBoardRef_);
		break;
	}

	std::uniform_int_distribution<> distrib2(0, 5);
	randomNumber = distrib2(rng);
	switch (randomNumber)
	{
	case 0:
		createdBlock->setColor(sf::Color::Red);
		break;
	case 1:
		createdBlock->setColor(sf::Color::Green);
		break;
	case 2:
		createdBlock->setColor(sf::Color::Blue);
		break;
	case 3:
		createdBlock->setColor(sf::Color::Yellow);
		break;
	case 4:
		createdBlock->setColor(sf::Color::Magenta);
		break;
	case 5:
		createdBlock->setColor(sf::Color::Cyan);
		break;
	}

	return createdBlock;
}
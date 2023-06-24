#pragma once

#include <random>
#include <memory>

class BaseBlock;
class BlockBoard;

class BlockCreator
{
public:
	BlockCreator() = delete;
	BlockCreator(const BlockCreator& other) = delete;
	BlockCreator(const BlockCreator&& other) = delete;
	~BlockCreator() = default;

	static std::unique_ptr<BaseBlock> createRandomBlock(BlockBoard& blockBoardRef_, std::random_device& rd) noexcept;
};

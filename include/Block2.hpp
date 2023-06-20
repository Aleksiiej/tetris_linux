#pragma once

#include "BaseBlock.hpp"

class Block2 : public BaseBlock
{
public:
	Block2() = delete;
	Block2(BlockBoard& blockBoardRef) noexcept;
	Block2(const Block2& other) = delete;
	Block2(const Block2&& other) = delete;
	~Block2() = default;
};

// *----*
// |0123|
// *----*

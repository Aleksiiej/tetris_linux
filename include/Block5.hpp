#pragma once

#include "BaseBlock.hpp"

class Block5 : public BaseBlock
{
public:
	Block5() = delete;
	Block5(BlockBoard& blockBoardRef) noexcept;
	Block5(const Block5& other) = delete;
	Block5(const Block5&& other) = delete;
	~Block5() = default;
};

// *---* *--* *---* *--*
// |012| | 0| |3  | |23|
// |  3| | 1| |210| |1 |
// *---* |32| *---* |0 |
//       *--*       *--*     

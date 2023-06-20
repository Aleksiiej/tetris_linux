#pragma once

#include "BaseBlock.hpp"

class Block3 : public BaseBlock
{
public:
	Block3() = delete;
	Block3(BlockBoard& blockBoardRef) noexcept;
	Block3(const Block3& other) = delete;
	Block3(const Block3&& other) = delete;
	~Block3() = default;
};

// *---* *---* *---* *---*
// |012| | 0 | | 3 | | 2 |
// | 3 | |31 | |210| | 13|
// *---* | 2 | *---* | 0 |
//       *---*       *---*       

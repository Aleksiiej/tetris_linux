#include "Block7.hpp"

Block7::Block7(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef)
{
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, 2 * GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
}

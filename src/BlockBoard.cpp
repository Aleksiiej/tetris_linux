#include "BlockBoard.hpp"

BlockBoard::BlockBoard(ScoreCounter& scoreCounter) noexcept : scoreCounter_(scoreCounter)
{
	for (uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
		{
			blockBoard_.at(i).at(j) = sf::Color::White;
		}
	}
}

void BlockBoard::handleFilledRows() noexcept
{
	const std::vector<uint8_t> vectorOfFilledRows{ checkWhichRowsFilled() };
	if (!vectorOfFilledRows.empty())
	{
		deleteFilledRows(vectorOfFilledRows);
		scoreCounter_.incrementScore();
	}
}

const std::vector<uint8_t> BlockBoard::checkWhichRowsFilled() const noexcept
{
	std::vector<uint8_t> filledRowsVec;
	uint8_t rowNumber{ 0 };
	uint8_t controlNumber{ 0 };
	for (uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		for (uint8_t j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			if (blockBoard_.at(j).at(i) != sf::Color::White)
			{
				controlNumber++;
			}
		}
		if (controlNumber == 10)
		{
			filledRowsVec.push_back(rowNumber);
		}
		rowNumber++;
		controlNumber = 0;
	}
	return filledRowsVec;
}

void BlockBoard::deleteFilledRows(const std::vector<uint8_t>& vectorOfRows) noexcept
{
	for (const auto& el : vectorOfRows)
	{
		for (auto& column : blockBoard_)
		{
			column.at(el) = sf::Color::White;
			for (uint8_t i = el; i > 0; i--)
			{
				column.at(i) = column.at(i - 1);
			}
		}
	}
}

void BlockBoard::clear() noexcept
{
	for (auto& innerArray : blockBoard_)
	{
		for (auto& el : innerArray)
		{
			el = sf::Color::White;
		}
	}
}

BoardArray& BlockBoard::getBoardArrayRef() noexcept
{
	return blockBoard_;
}

void BlockBoard::setFillColor(const uint8_t& x, const uint8_t& y, const sf::Color& color) noexcept
{
	blockBoard_.at(x).at(y) = color;
}

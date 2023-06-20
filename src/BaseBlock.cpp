#include "BaseBlock.hpp"

BaseBlock::BaseBlock(BlockBoard& blockBoardRef) noexcept : blockBoardRef_(blockBoardRef)
{
	std::ranges::for_each(blockArray_, [](auto& block) { block = sf::RectangleShape{ sf::Vector2f{ GRID, GRID } }; });
}

void BaseBlock::fall() noexcept
{
	std::ranges::for_each(blockArray_, [](auto& block) { block.move(0, GRID); });
}

void BaseBlock::moveRight() noexcept
{
	if (isMoveRightPossible())
	{
		std::ranges::for_each(blockArray_, [](auto& block) { block.move(GRID, 0); });
	}
}

void BaseBlock::moveLeft() noexcept
{
	if (isMoveLeftPossible())
	{
		std::ranges::for_each(blockArray_, [](auto& block) { block.move(-GRID, 0); });
	}
}

void BaseBlock::moveDown() noexcept
{
	while (isFallingPossible())
	{
		std::ranges::for_each(blockArray_, [](auto& block) { block.move(0, GRID); });
	}
}

void BaseBlock::rotate() noexcept
{
	if (isRotationPossible())
	{
		float newX{ 0 };
		float newY{ 0 };
		for (auto& el : blockArray_)
		{
			newX = blockArray_.at(1).getPosition().x + blockArray_.at(1).getPosition().y - el.getPosition().y;
			newY = blockArray_.at(1).getPosition().y - blockArray_.at(1).getPosition().x + el.getPosition().x;
			el.setPosition(newX, newY);
		}
	}
}

const bool BaseBlock::isFallingPossible() const noexcept
{
	auto blockCoords = getCoords();
	auto newCoords{ blockCoords };
	std::ranges::for_each(newCoords, [](auto& coords) { coords.second += GRID; });
	extractAdjacentCoords(blockCoords, newCoords);

	for (const auto& field : newCoords)
	{
		if (field.second > GRID * NUMBER_OF_ROWS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
	}
	return true;
}

const bool BaseBlock::isMoveRightPossible() const noexcept
{
	auto blockCoords = getCoords();
	auto newCoords{ blockCoords };
	std::ranges::for_each(newCoords, [](auto& coords) { coords.first += GRID; });
	extractAdjacentCoords(blockCoords, newCoords);

	for (const auto& field : newCoords)
	{
		if (field.first > GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White)
		{
			return false;
		}
	}
	return true;
}

const bool BaseBlock::isMoveLeftPossible() const noexcept
{
	auto blockCoords = getCoords();
	auto newCoords{ blockCoords };
	std::ranges::for_each(newCoords, [](auto& coords) { coords.first -= GRID; });
	extractAdjacentCoords(blockCoords, newCoords);

	for (const auto& field : newCoords)
	{
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White
			or field.first <= 0)
		{
			return false;
		}
	}
	return true;
}

const bool BaseBlock::isRotationPossible() const noexcept
{
	float newX{ 0 };
	float newY{ 0 };
	std::vector<std::pair<float, float>> newCoords;
	for (const auto& el : blockArray_)
	{
		newX = blockArray_.at(1).getPosition().x + blockArray_.at(1).getPosition().y - el.getPosition().y;
		newY = blockArray_.at(1).getPosition().y - blockArray_.at(1).getPosition().x + el.getPosition().x;
		newCoords.push_back({ newX, newY });
	}
	for (auto& el : newCoords)
	{
		if (el.first < GRID
			or el.first > GRID * NUMBER_OF_COLUMNS
			or el.second < GRID
			or el.second > GRID * NUMBER_OF_ROWS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(el.first)).at(gridToY(el.second)) != sf::Color::White)
		{
			return false;
		}
	}
	return true;
}

const bool BaseBlock::checkIfLost() const noexcept
{
	for (uint8_t i = 0; i < 4; i++)
	{
		if (blockArray_.at(i).getPosition().y == GRID
			and blockBoardRef_.getBoardArrayRef().at(gridToX(i)).at(gridToY(i)) != sf::Color::White)
		{
			return true;
		}
	}
	return false;
}

void BaseBlock::setColor(const sf::Color& color) noexcept
{
	std::ranges::for_each(blockArray_, [&](auto& block) { block.setFillColor(color); });
}

const std::array<sf::RectangleShape, 4>& BaseBlock::getBlockArrayRef() const noexcept
{
	return blockArray_;
}

void BaseBlock::setColorsInBlockBoard() const noexcept
{
	for (uint8_t i = 0; i < 4; i++)
	{
		blockBoardRef_.setFillColor(gridToX(i), gridToY(i), blockArray_.at(0).getFillColor());
	}
}

const std::vector<std::pair<float, float>> BaseBlock::getCoords() const noexcept
{
	std::vector<std::pair<float, float>> blockCoords;
	for (uint8_t i = 0; i < 4; i++)
	{
		blockCoords.push_back(std::make_pair(blockArray_.at(i).getPosition().x, blockArray_.at(i).getPosition().y));
	}
	return blockCoords;
}

void BaseBlock::extractAdjacentCoords(std::vector<std::pair<float, float>>& blockCoords, std::vector<std::pair<float, float>>& newCoords) const noexcept
{
	for (auto It = begin(newCoords); It != end(newCoords); It++)
	{
		if (std::ranges::any_of(blockCoords, [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			newCoords.erase(It);
			It = begin(newCoords);
		}
	}
}

const int BaseBlock::gridToX(const float& blockNumber) const noexcept
{
	if (blockNumber >= 0 and blockNumber < 5)
	{
		return static_cast<int>((blockArray_.at(static_cast<std::size_t>(blockNumber)).getPosition().x - GRID) / GRID);
	}
	else return static_cast<int>((blockNumber - GRID) / GRID);
}

const int BaseBlock::gridToY(const float& blockNumber) const noexcept
{
	if (blockNumber >= 0 and blockNumber < 5)
	{
		return static_cast<int>((blockArray_.at(static_cast<std::size_t>(blockNumber)).getPosition().y - GRID) / GRID);
	}
	else return static_cast<int>((blockNumber - GRID) / GRID);
}
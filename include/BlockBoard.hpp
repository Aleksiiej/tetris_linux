#pragma once

#include <array>

#include "GlobalValues.hpp"
#include "ScoreCounter.hpp"

using BoardArray = std::array<std::array<sf::Color, NUMBER_OF_ROWS>, NUMBER_OF_COLUMNS>;

class BlockBoard
{
public:
	BlockBoard(ScoreCounter& scoreCounter) noexcept;
	BlockBoard(const BlockBoard& other) = delete;
	BlockBoard(const BlockBoard&& other) = delete;
	~BlockBoard() = default;

	void handleFilledRows() noexcept;
	const std::vector<uint8_t> checkWhichRowsFilled() const noexcept;
	void deleteFilledRows(const std::vector<uint8_t>& vectorOfRows) noexcept;
	void clear() noexcept;

	BoardArray& getBoardArrayRef() noexcept;
	void setFillColor(const uint8_t& x, const uint8_t& y, const sf::Color& color) noexcept;

private:
	BoardArray blockBoard_;
	ScoreCounter& scoreCounter_;
};

#pragma once

#include <cstdint>

constexpr uint8_t NUMBER_OF_ROWS = 20;
constexpr uint8_t NUMBER_OF_COLUMNS = 10;
constexpr uint8_t GRID = 25;
constexpr uint8_t GAME_SPEED = 200;

enum class GameStatus
{
	Ongoing, Lost
};

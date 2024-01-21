#pragma once

#include "Band.hpp"
#include "BlockCreator.hpp"
#include "BaseBlock.hpp"
#include "EndgameText.hpp"
#include "StartgameText.hpp"

#include <optional>

class Game
{
public:
	Game() noexcept;
	Game(const Game &other) = delete;
	Game(const Game &&other) = delete;
	~Game() = default;

	static std::optional<std::unique_ptr<Game>> createInstance() noexcept;
	void run() noexcept;

private:
	sf::RenderWindow window_{sf::VideoMode{800, 600}, "Tetris", sf::Style::Titlebar | sf::Style::Close};
	sf::Event event_;
	GameStatus gameStatus_{GameStatus::Ongoing};
	const Band band_{GRID, GRID};
	const StartgameText startgameText_;
	const EndgameText endgameText_;
	ScoreCounter scoreCounter_;
	BlockBoard blockBoard_{scoreCounter_};
	std::random_device rd_;
	std::unique_ptr<BaseBlock> ptrToBlock_ = BlockCreator::createRandomBlock(blockBoard_, rd_);
	sf::Clock clock_;
	static uint8_t numOfInstances;

	void processInput() noexcept;
	void update() noexcept;
	void render(bool startgame, bool endgame) noexcept;
	void waitForInput() noexcept;
	void resetGame() noexcept;
};
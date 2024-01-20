#pragma once

#include "Band.hpp"
#include "BlockCreator.hpp"
#include "BaseBlock.hpp"
#include "EndgameText.hpp"
#include "StartgameText.hpp"

class Game
{
public:
    Game() noexcept;
    void run();
	void gameLoop() noexcept;
	void processInput() noexcept;
	void update() noexcept;
	std::unique_ptr<BaseBlock> render(const Band &band, BlockBoard &blockBoardRef, const ScoreCounter &scoreCounter, sf::RenderWindow &window, bool startgame, bool endgame, std::unique_ptr<BaseBlock> ptrToBlock = nullptr) noexcept;

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

    void resetGame(GameStatus &gameStatus, BlockBoard &blockBoard, ScoreCounter &scoreCounter) noexcept;
};
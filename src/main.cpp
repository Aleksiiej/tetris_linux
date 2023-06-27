#include "Band.hpp"
#include "BlockCreator.hpp"
#include "BaseBlock.hpp"
#include "EndgameText.hpp"
#include "StartgameText.hpp"

std::unique_ptr<BaseBlock> drawBoard(const Band& band, BlockBoard& blockBoardRef, const ScoreCounter& scoreCounter, sf::RenderWindow& window, std::unique_ptr<BaseBlock> ptrToBlock = nullptr) noexcept;
void resetGame(GameStatus& gameStatus, BlockBoard& blockBoard, ScoreCounter& scoreCounter) noexcept;

int main()
{
	sf::RenderWindow window{ sf::VideoMode{800, 600}, "Tetris", sf::Style::Titlebar | sf::Style::Close };
	window.setFramerateLimit(60);
	sf::Event event;

	GameStatus gameStatus{ GameStatus::Ongoing };
	const Band band{ GRID, GRID };
	const StartgameText StartgameText;
	const EndgameText endgameText;
	ScoreCounter scoreCounter;
	BlockBoard blockBoard{ scoreCounter };
	std::random_device rd;
	std::unique_ptr<BaseBlock> ptrToBlock = std::move(BlockCreator::createRandomBlock(blockBoard, rd));
	sf::Clock clock;

	while (true)
	{
		window.clear(sf::Color::White);

		if (gameStatus == GameStatus::Ongoing)
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::EventType::KeyPressed)
				{
					switch (event.key.code)
					{
					case sf::Keyboard::Right:
						ptrToBlock->moveRight();
						break;

					case sf::Keyboard::Left:
						ptrToBlock->moveLeft();
						break;

					case sf::Keyboard::Down:
						ptrToBlock->moveDown();
						break;

					case sf::Keyboard::Space:
						ptrToBlock->rotate();
						break;

					default:
						break;
					}
				}
				else if (event.type == sf::Event::EventType::Closed)
				{
					window.close();
					return 0;
				}
			}
			ptrToBlock = drawBoard(band, blockBoard, scoreCounter, window, std::move(ptrToBlock));
			window.display();
			if (ptrToBlock->isFallingPossible())
			{
				if (clock.getElapsedTime() >= sf::milliseconds(GAME_SPEED))
				{
					ptrToBlock->fall();
					blockBoard.handleFilledRows();
					clock.restart();
				}
			}
			else
			{
				ptrToBlock.reset(nullptr);
				ptrToBlock = std::move(BlockCreator::createRandomBlock(blockBoard, rd));
				if (ptrToBlock->checkIfLost())
				{
					gameStatus = GameStatus::Lost;
				}
			}
		}
		else if (gameStatus == GameStatus::Lost)
		{
			drawBoard(band, blockBoard, scoreCounter, window);
			window.draw(endgameText);
			window.display();
			while (window.waitEvent(event))
			{
				if (event.type == sf::Event::EventType::Closed or event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					return 0;
				}
				if (event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Space)
				{
					break;
				}
			}
			resetGame(gameStatus, blockBoard, scoreCounter);
		}
	}
	return 0;
}

std::unique_ptr<BaseBlock> drawBoard(const Band& band, BlockBoard& blockBoardRef, const ScoreCounter& scoreCounter, sf::RenderWindow& window, std::unique_ptr<BaseBlock> ptrToBlock) noexcept
{
	window.draw(band);
	window.draw(scoreCounter);

	sf::RectangleShape singleField; // TODO: figure out how to use smaller class than RectangleShape
	singleField.setSize(sf::Vector2f{ GRID, GRID });
	for (uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
		{
			singleField.setFillColor(blockBoardRef.getBoardArrayRef().at(i).at(j));
			singleField.setPosition(static_cast<float>(i * GRID + GRID), static_cast<float>(j * GRID + GRID));
			window.draw(singleField);
		}
	}
	if (ptrToBlock)
	{
		for (const auto& block : ptrToBlock->getBlockArrayRef())
		{
			window.draw(block);
		}
	}

	return ptrToBlock;
}

void resetGame(GameStatus& gameStatus, BlockBoard& blockBoard, ScoreCounter& scoreCounter) noexcept
{
	gameStatus = GameStatus::Ongoing;
	blockBoard.clear();
	scoreCounter.reset();
}

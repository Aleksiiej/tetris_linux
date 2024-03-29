#include "Game.hpp"

uint8_t Game::numOfInstances = 0;

Game::Game() noexcept
{
    window_.setFramerateLimit(60);
}

std::optional<std::unique_ptr<Game>> Game::createInstance() noexcept
{
    if (!numOfInstances)
    {
        numOfInstances++;
        return std::optional<std::unique_ptr<Game>>{std::make_unique<Game>()};
    }
    else
        return std::nullopt;
}

void Game::run() noexcept
{
    render(true, false);
    waitForInput();

    while (true)
    {
        if (gameStatus_ == GameStatus::Ongoing)
        {
            processInput();
            render(false, false);
            update();
        }
        else if (gameStatus_ == GameStatus::Lost)
        {
            render(false, true);
            waitForInput();
            resetGame();
        }
    }
}

void Game::processInput() noexcept
{
    while (window_.pollEvent(event_))
    {
        if (event_.type == sf::Event::EventType::KeyPressed)
        {
            switch (event_.key.code)
            {
            case sf::Keyboard::Right:
                ptrToBlock_->moveRight();
                break;

            case sf::Keyboard::Left:
                ptrToBlock_->moveLeft();
                break;

            case sf::Keyboard::Down:
                ptrToBlock_->moveDown();
                break;

            case sf::Keyboard::Space:
                ptrToBlock_->rotate();
                break;

            case sf::Keyboard::P:
                while (window_.waitEvent(event_))
                {
                    if (event_.type == sf::Event::EventType::KeyPressed and event_.key.code == sf::Keyboard::P)
                    {
                        break;
                    }
                }
                break;

            case sf::Keyboard::Escape:
                window_.close();
                exit(0);
            default:
                break;
            }
        }
        else if (event_.type == sf::Event::EventType::Closed)
        {
            window_.close();
            exit(0);
        }
    }
}

void Game::update() noexcept
{
    if (ptrToBlock_->isFallingPossible())
    {
        if (clock_.getElapsedTime() >= sf::milliseconds(GAME_SPEED))
        {
            ptrToBlock_->fall();
            blockBoard_.handleFilledRows();
            clock_.restart();
        }
    }
    else
    {
        ptrToBlock_.reset(nullptr);
        ptrToBlock_ = std::move(BlockCreator::createRandomBlock(blockBoard_, rd_));
        if (ptrToBlock_->checkIfLost())
        {
            gameStatus_ = GameStatus::Lost;
        }
    }
}

void Game::render(bool startgame, bool endgame) noexcept
{
    window_.clear(sf::Color::White);

    window_.draw(band_);
    window_.draw(scoreCounter_);

    sf::RectangleShape singleField; // TODO: figure out how to use smaller class than RectangleShape
    singleField.setSize(sf::Vector2f{GRID, GRID});
    for (uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
    {
        for (uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
        {
            singleField.setFillColor(blockBoard_.getBoardArrayRef().at(i).at(j));
            singleField.setPosition(static_cast<float>(i * GRID + GRID), static_cast<float>(j * GRID + GRID));
            window_.draw(singleField);
        }
    }
    if (!startgame)
    {
        for (const auto &block : ptrToBlock_->getBlockArrayRef())
        {
            window_.draw(block);
        }
    }
    if (startgame)
    {
        window_.draw(startgameText_);
    }
    if (endgame)
    {
        window_.draw(endgameText_);
    }
    window_.display();
}

void Game::waitForInput() noexcept
{
    while (window_.waitEvent(event_))
    {
        if (event_.type == sf::Event::EventType::KeyPressed and event_.key.code == sf::Keyboard::Space)
        {
            break;
        }
        if (event_.type == sf::Event::EventType::Closed or event_.key.code == sf::Keyboard::Escape)
        {
            window_.close();
            exit(0);
        }
    }
}

void Game::resetGame() noexcept
{
    gameStatus_ = GameStatus::Ongoing;
    blockBoard_.clear();
    scoreCounter_.reset();
}
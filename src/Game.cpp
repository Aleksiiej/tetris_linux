#include "Game.hpp"

Game::Game() noexcept
{
    window_.setFramerateLimit(60);
}

void Game::run()
{
    window_.clear(sf::Color::White);
    render(true, false);

    while (window_.waitEvent(event_))
    {
        if (event_.type == sf::Event::EventType::KeyPressed and event_.key.code == sf::Keyboard::Enter)
        {
            break;
        }
        if (event_.type == sf::Event::EventType::Closed or event_.key.code == sf::Keyboard::Escape)
        {
            window_.close();
            return;
        }
    }

    while (true)
    {
        window_.clear(sf::Color::White);

        if (gameStatus_ == GameStatus::Ongoing)
        {
            processInput();
            ptrToBlock_ = render(false, false, std::move(ptrToBlock_));
            update();
        }
        else if (gameStatus_ == GameStatus::Lost)
        {
            ptrToBlock_ = render(false, true, std::move(ptrToBlock_));
            while (window_.waitEvent(event_))
            {
                if (event_.type == sf::Event::EventType::KeyPressed and event_.key.code == sf::Keyboard::Space)
                {
                    break;
                }
                if (event_.type == sf::Event::EventType::Closed or event_.key.code == sf::Keyboard::Escape)
                {
                    window_.close();
                    return;
                }
            }
            resetGame(gameStatus_, blockBoard_, scoreCounter_);
        }
    }
}

void Game::gameLoop() noexcept
{
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

std::unique_ptr<BaseBlock> Game::render(bool startgame, bool endgame, std::unique_ptr<BaseBlock> ptrToBlock_) noexcept
{
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
    if (ptrToBlock_)
    {
        for (const auto &block : ptrToBlock_->getBlockArrayRef())
        {
            window_.draw(block);
        }
    }
    if(startgame)
    {
        window_.draw(startgameText_);
    }
    if(endgame)
    {
        window_.draw(endgameText_);
    }
    window_.display();
    return ptrToBlock_;
}

void Game::resetGame(GameStatus &gameStatus_, BlockBoard &blockBoard_, ScoreCounter &scoreCounter_) noexcept
{
    gameStatus_ = GameStatus::Ongoing;
    blockBoard_.clear();
    scoreCounter_.reset();
}
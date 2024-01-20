#include "Game.hpp"

Game::Game() noexcept
{
    window_.setFramerateLimit(60);
}

void Game::run()
{
    window_.clear(sf::Color::White);
    drawBoard(band_, blockBoard_, scoreCounter_, window_);
    window_.draw(startgameText_);
    window_.display();

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
            ptrToBlock_ = drawBoard(band_, blockBoard_, scoreCounter_, window_, std::move(ptrToBlock_));
            window_.display();
            update();
        }
        else if (gameStatus_ == GameStatus::Lost)
        {
            drawBoard(band_, blockBoard_, scoreCounter_, window_);
            window_.draw(endgameText_);
            window_.display();
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

void Game::render(bool endgame) noexcept
{
    drawBoard(band_, blockBoard_, scoreCounter_, window_);
    if(endgame)
    {
        window_.draw(endgameText_);
    }
    window_.display();
}

std::unique_ptr<BaseBlock> Game::drawBoard(const Band &band_, BlockBoard &blockBoardRef_, const ScoreCounter &scoreCounter_, sf::RenderWindow &window_, std::unique_ptr<BaseBlock> ptrToBlock_) noexcept
{
    window_.draw(band_);
    window_.draw(scoreCounter_);

    sf::RectangleShape singleField; // TODO: figure out how to use smaller class than RectangleShape
    singleField.setSize(sf::Vector2f{GRID, GRID});
    for (uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
    {
        for (uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
        {
            singleField.setFillColor(blockBoardRef_.getBoardArrayRef().at(i).at(j));
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

    return ptrToBlock_;
}

void Game::resetGame(GameStatus &gameStatus_, BlockBoard &blockBoard_, ScoreCounter &scoreCounter_) noexcept
{
    gameStatus_ = GameStatus::Ongoing;
    blockBoard_.clear();
    scoreCounter_.reset();
}
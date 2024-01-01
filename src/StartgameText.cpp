#include "StartgameText.hpp"

StartgameText::StartgameText() noexcept
{
	font_.loadFromFile("../content/Ldfcomicsans-jj7l.ttf");
	text_.setFont(font_);
	text_.setString("Welcome in Tetris!\n\n"
                    "INSTRUCTIONS:\n"
                    "LEFT and RIGHT arrow keys to move blocks\n"
                    "left and right\n"
                    "SPACE to rotate block\n"
                    "DOWN arrow key to drop block to the bottom\n"
                    "of the board\n"
                    "P to pause and unpause game\n\n"
                    "Click ENTER to start game");
	text_.setCharacterSize(20);
	text_.setFillColor(sf::Color::Red);
	text_.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text_.setPosition(300, 200);
}

void StartgameText::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(text_, states);
}

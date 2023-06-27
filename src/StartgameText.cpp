#include "StartgameText.hpp"

StartgameText::StartgameText() noexcept
{
	font_.loadFromFile(fontFilePath + "Ldfcomicsans-jj7l.ttf");
	text_.setFont(font_);
	text_.setString("Welcome in Tetris!\n"
                    "INSTRUCTIONS: LEFT and RIGHT arrow keys to move blocks left and right\n"
                    "SPACE to rotate block\n"
                    "DOWN arrow key to drop block to the bottom of the board\n"
                    "P to pause game\n\n"
                    "Click SPACE to start game");
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Red);
	text_.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text_.setPosition(300, 400);
}

void StartgameText::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(text_, states);
}

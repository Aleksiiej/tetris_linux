#include "EndgameText.hpp"

EndgameText::EndgameText() noexcept
{
	font_.loadFromFile(fontFilePath);
	text_.setFont(font_);
	text_.setString("You loose!\nClick ESCAPE button to close game\nOr Space to begin new game");
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Red);
	text_.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text_.setPosition(300, 400);
}

void EndgameText::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(text_, states);
}

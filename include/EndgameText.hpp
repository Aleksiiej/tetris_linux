#pragma once

#include <SFML/Graphics.hpp>

class EndgameText : public sf::Drawable
{
public:
	EndgameText() noexcept;
	EndgameText(const EndgameText& other) = delete;
	EndgameText(const EndgameText&& other) = delete;
	~EndgameText() = default;

private:
	sf::Font font_;
	sf::Text text_;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
};

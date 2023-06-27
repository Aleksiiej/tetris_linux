#pragma once

#include "GlobalValues.hpp"
#include <SFML/Graphics.hpp>

class StartgameText : public sf::Drawable
{
public:
	StartgameText() noexcept;
	StartgameText(const StartgameText& other) = delete;
	StartgameText(const StartgameText&& other) = delete;
	~StartgameText() = default;

private:
	sf::Font font_;
	sf::Text text_;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
};

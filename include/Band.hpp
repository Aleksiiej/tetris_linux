#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalValues.hpp"

class Band : public sf::Drawable
{
public:
	Band(const uint8_t& bandX, const uint8_t& bandY) noexcept;
	Band() = delete;
	Band(const Band& other) = delete;
	Band(const Band&& other) = delete;
	~Band() = default;

private:
	sf::RectangleShape band_{};
	const sf::Vector2f size_{ NUMBER_OF_COLUMNS * GRID, NUMBER_OF_ROWS * GRID };

	void draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
};

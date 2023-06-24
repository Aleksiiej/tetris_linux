#pragma once

#include <SFML/Graphics.hpp>

class ScoreCounter : public sf::Drawable
{
public:
	ScoreCounter() noexcept;
	ScoreCounter(const ScoreCounter& other) = delete;
	ScoreCounter(const ScoreCounter&& other) = delete;
	~ScoreCounter() = default;

	void incrementScore() noexcept;
	void reset() noexcept;

private:
	short int score_;
	sf::Font font_;
	sf::Text text_;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
};

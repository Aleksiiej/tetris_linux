#include "Band.hpp"
#include "BlockCreator.hpp"
#include "BaseBlock.hpp"
#include "EndgameText.hpp"
#include "Game.hpp"
#include "StartgameText.hpp"

int main()
{
	auto game = Game::createInstance();
	if (game.has_value())
	{
		game.value()->run();
	}
	return 0;
}

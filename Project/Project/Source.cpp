#include <iostream>
#include "Game.h"
#include "HomeScreen.h"
#include "Gui/Button.hpp"

using namespace sf;

int main()
{
	gui::Button button = gui::Button(button);

	srand(time(NULL));
	HomeScreen home;
	while (home.running() && !home.difficultyChoosen())
	{
		home.update();
		home.render();
	}
	if (home.difficulty == 0) return 0;
	Game game(home.difficulty);
	home.window->close();
	while (game.running() && !game.isEndGame())
	{
		game.update();

		game.render();
	}
	game.window->close();
	HomeScreen end;
	end.difficulty = 1;
	while (end.running())
	{
		end.pollEvent();
		end.renderEndScreen(game.points);
	}
}
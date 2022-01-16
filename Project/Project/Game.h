#pragma once

/*
	@SOME NOTES

	- Ctrl + . : create function from .h to .cpp
	- Ctrl + K + C : comment
	- Ctrl + K + U : uncomment

*/
#pragma region Libararies and Namespaces

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
using namespace sf;

#pragma endregion

class Game
{
private:
	sf::Event event;
	sf::VideoMode vidMode;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//resources
	sf::Font font;
	sf::Text uiText;

	//game logic
	int health;
	float enemySpawnTimer, enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool endGame;

	//game objects
	sf::RectangleShape enemy;
	vector <sf::RectangleShape> enemies;

	void initVariables();
	void initWindow();
	void initEnemy();
	void initFont();
	void initText();

	void pollEvents();

	void spawnEnemy();
	void updateEnemies();
	void updateText();
	void updateMousePosition();

	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);

public:
	RenderWindow* window;
	unsigned points;

	//instructor, destructor
	Game(int difficulty);
	virtual ~Game();
	int difficulty;
	//public functions for main
	const bool running() const;
	const bool isEndGame() const;
	void update();
	void render();
};


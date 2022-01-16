#pragma once

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

class HomeScreen
{
private:
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Event event;
	Font font;
	Text uiText[3];

	RectangleShape box[2];

	void initWindow();
	void initFont();
	void initText();
	void initBox();

	void updateMousePos();

	void renderTexts();
	void renderBoxes();

public:
	RenderWindow* window;
	HomeScreen();
	int difficulty;
	virtual ~HomeScreen();
	void update();
	void render();
	void renderEndScreen(int points);
	void pollEvent();
	const bool running() const;
	const bool difficultyChoosen() const;
};
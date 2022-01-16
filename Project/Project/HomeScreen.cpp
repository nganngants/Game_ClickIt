#include "HomeScreen.h"

void HomeScreen::initWindow()
{
	difficulty = 0;
	this->window = new RenderWindow(VideoMode(600, 600), "Practice your mouse skill!", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void HomeScreen::initFont()
{
	this->font.loadFromFile("Fonts/FELIXTI.TTF");
}

void HomeScreen::initText()
{
	for (int i = 0; i < 3; ++i)
	{
		uiText[i].setFont(font);
		uiText[i].setFillColor(Color::White);
		uiText[i].setCharacterSize(30);
		uiText[i].setStyle(Text::Bold);
	}
	uiText[0].setString("CHOOSE DIFFICULTY");
	uiText[1].setString("EASY");
	uiText[2].setString("HARD");
	uiText[0].setPosition(153.f, 125.f);
	uiText[1].setPosition(262.f, 231.f);
	uiText[2].setPosition(251.f, 431.f);
}

void HomeScreen::initBox()
{
	for (int i = 0; i < 2; ++i)
	{
		box[i].setFillColor(Color(104, 103, 172));
		box[i].setSize(Vector2f(200.f, 100.f));
	}
	box[0].setPosition(Vector2f(200.f, 200.f));
	box[1].setPosition(Vector2f(200.f, 400.f));
}

void HomeScreen::updateMousePos()
{
	mousePosWindow = Mouse::getPosition(*this->window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void HomeScreen::pollEvent()
{
	while (window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			window->close(); break;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) window->close(); break;
		}
	}
}

void HomeScreen::renderTexts()
{
	for (int i = 0; i < 3; ++i) window->draw(uiText[i]);
}

void HomeScreen::renderBoxes()
{
	for (int i = 0; i < 2; ++i) window->draw(box[i]);
}

HomeScreen::HomeScreen()
{
	initWindow();
	initBox();
	initFont();
	initText();
}

HomeScreen::~HomeScreen()
{
	delete window;
}

void HomeScreen::update()
{
	pollEvent();
	if (!difficulty)
	{
		updateMousePos();
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			int pos = -1;
			for (int i = 0; i < 2; ++i)
				if (box[i].getGlobalBounds().contains(mousePosView))
					pos = i;
			difficulty = pos + 1;
		}
	}
}

void HomeScreen::render()
{
	this->window->clear(Color(234, 153, 213));

	//Draw game objects here
	renderBoxes();
	renderTexts();
	this->window->display();
}

void HomeScreen::renderEndScreen(int points)
{
	stringstream ss;
	uiText[0].setString("GAME OVER!");
	uiText[0].setPosition(190.f, 125.f);

	ss << "Your point is: " << points;
	uiText[1].setString(ss.str());
	uiText[1].setCharacterSize(20);
	uiText[1].setPosition(193.f, 175.f);

	uiText[2].setString("                  If you want to play again,\nplease exit this and restart the program again :D");
	uiText[2].setCharacterSize(13);
	uiText[2].setPosition(107.f, 225.f);

	this->window->clear(Color(234, 153, 213));
	for (int i = 0; i < 3; ++i) window->draw(uiText[i]);
	window->display();
}

const bool HomeScreen::running() const
{
	return window->isOpen();
}

const bool HomeScreen::difficultyChoosen() const
{
	return (difficulty != 0);
}


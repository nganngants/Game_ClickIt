#pragma region some defines

#include "Game.h"
#define RAND(l,r) rand()%(r-l+1)+l
#define sz(a) (int)a.size()

#pragma endregion

#pragma region Public Functions

//check if the game is running by checking if the window is still open
const bool Game::running() const
{
	return window->isOpen();
}

const bool Game::isEndGame() const
{
	return this->endGame;
}

void Game::render()
{
	/*
		@return void

		- clear old frames
		- draw, render objects
		- display frames

		Renders the game objects
	*/

	this->window->clear(Color(234, 153, 213));

	//Draw game objects here
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}

void Game::update()
{
	pollEvents();
	if (!endGame)
	{
		updateMousePosition();
		updateEnemies();
		updateText();
	}
}

#pragma endregion

#pragma region Init

void Game::initVariables()
{
	this->window = nullptr;
	this->vidMode.height = 800;
	this->vidMode.width = 1000;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = difficulty == 1 ? 8 : 10;
	this->mouseHeld = this->endGame = false;
	this->points = 0;
	this->health = 10;
}

void Game::initWindow()
{
	this->window = new RenderWindow(vidMode, "Practice your mouse skill!", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	//remember to set object's position and size first
	this->enemy.setPosition(27.f, 27.f);
	//and then set other properties
	this->enemy.setOutlineColor(Color::Cyan);
	this->enemy.setOutlineThickness(2.f);
}

void Game::initFont()
{
	this->font.loadFromFile("Fonts/FELIXTI.TTF");
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setFillColor(Color::White);
	this->uiText.setCharacterSize(24);
	this->uiText.setStyle(sf::Text::Bold);
}

Game::Game(int difficulty)
{
	this->difficulty = difficulty;
	initVariables();
	initWindow();
	initEnemy();
	initFont();
	initText();
}

Game::~Game()
{
	delete window;
}
#pragma endregion

#pragma region Update

void Game::pollEvents()
{
	/*
		@return void

		- poll event
		- check event type by switch case

	*/
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


void Game::updateMousePosition()
{
	/*
		@return void
		update mouse position 
		- relative to the window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);

	//relative to the screen
	//std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << '\n';
}

void Game::spawnEnemy()
{
	/*
		@return void
		Spawn new enemy
		- Sets random color and positon
		- Adds enemy to the vector
	*/
	int type = rand() % 3;

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.f
	);
	switch (type)
	{
	case 0: 
		enemy.setFillColor(Color::Red);
		enemy.setSize(Vector2f(20.f, 20.f));
		break;
	case 1:
		enemy.setFillColor(Color::Blue);
		enemy.setSize(Vector2f(30.f, 30.f));
		break;
	case 2:
		enemy.setFillColor(Color::Green);
		enemy.setSize(Vector2f(45.f, 45.f));
		break;
	}
	this->enemies.push_back(enemy);
}

void Game::updateEnemies()
{
	/*
		@return void
		- Updates the enemy spawn timer and spawns new enemy
		when the total of enemies is smaller than the maximum
		- Move the enemies downward
		- Removes enemies at the edge of the screen
	*/

	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer == enemySpawnTimerMax)
		{
			this->enemySpawnTimer = 0.f;
			spawnEnemy();
		}
		else this->enemySpawnTimer += 1.f;
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		if (difficulty == 1) enemies[i].move(0.f, 3.f);
		else enemies[i].move(0.f, 5.8f);
		if (enemies[i].getPosition().y > window->getSize().y)
		{
			enemies.erase(enemies.begin() + i);
			health--;
			//cout << health << '\n';
			if (health == 0)
			{
				endGame = true;
				return;
			}
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (!mouseHeld)
		{
			mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < sz(enemies) && !deleted; i++)
				if (enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;
					Color color = enemies[i].getFillColor();
					enemies.erase(enemies.begin() + i);
					if (color == Color::Red) points += 10;
					else if (color == Color::Blue) points += 5;
					else points += 1;
				}
		}
	}
	else mouseHeld = false;
}

void Game::updateText()
{
	stringstream ss;
	ss << "Point: " << points << '\n'
		<< "Health: " << health << '\n';
	this->uiText.setString(ss.str());
}

#pragma endregion

#pragma region Render


void Game::renderText(sf::RenderTarget& target)
{
	target.draw(uiText);
}


void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto en : this->enemies) target.draw(en);
}

#pragma endregion

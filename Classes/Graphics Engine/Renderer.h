#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Main.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "..\Global Constants\GlobalConstants.h"

class Renderer
{
// PUBLIC FUNCTIONS
public:
	Renderer();
	~Renderer();

	void update();

	void drawSprite(sf::Sprite sprite);

// PUBLIC VARIABLES
public:
	sf::RenderWindow* window;
	sf::Text textMessage;

// PRIVATE FUNCTIONS
private:
	void initWindow();
	void initVariables();
	void initFont();
	void initText();

	void pollEvents();

// PRIVATE VARIABLES
private:
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Font font;
	
};
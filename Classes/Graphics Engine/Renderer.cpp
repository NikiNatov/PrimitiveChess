#include "Renderer.h"

// PUBLIC FUNCTIONS
Renderer::Renderer()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Renderer::~Renderer()
{
	delete this->window;
}

void Renderer::update()
{
	this->pollEvents();
}

void Renderer::drawSprite(sf::Sprite sprite)
{
	this->window->draw(sprite);
}

// PRIVATE FUNCTIONS
void Renderer::initWindow()
{
	this->videoMode.width = SCREEN_WIDTH;
	this->videoMode.height = SCREEN_WIDTH;

	this->window = new sf::RenderWindow(this->videoMode, "Chess");
}

void Renderer::initVariables()
{
	this->window = nullptr;
}

void Renderer::initFont()
{
	this->font.loadFromFile("Fonts/Merriweather-Bold.ttf");
}

void Renderer::initText()
{
	this->textMessage.setFont(this->font);
	this->textMessage.setCharacterSize(80);
	this->textMessage.setFillColor(sf::Color::Green);
	this->textMessage.setString(" ");
}

void Renderer::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

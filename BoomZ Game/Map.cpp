#include "Map.h"

Map::Map(sf::RenderWindow  *window)
{    
	this->window = window;
}
void Map::update(int n)
{
	this->n = n;
	char file = '0' + n;
	std::string FileAddress = "Picture/map/";
	FileAddress += file;
	sf::Texture textureBack, textureGround;
	this->textureBack.push_back(textureBack);
	this->textureGround.push_back(textureGround);

	this->textureBack[n-1].loadFromFile(FileAddress + "/back.jpg");
	this->textureGround[n-1].loadFromFile(FileAddress + "/ground.png");

	sf::Sprite spriteBack, spriteGround;

	spriteBack.setTexture(this->textureBack[n - 1]);
	spriteGround.setTexture(this->textureGround[n - 1]);

	spriteGround.setScale(sf::Vector2f(window->getSize().x / (float)this->textureGround[n - 1].getSize().x, window->getSize().y / (float)this->textureGround[n - 1].getSize().y));
	spriteBack.setScale(sf::Vector2f(window->getSize().x / (float)this->textureBack[n - 1].getSize().x, window->getSize().y / (float)this->textureBack[n - 1].getSize().y));
	this->spriteBack = spriteBack;
	this->spriteGround = spriteGround;
}
void Map::draw()
{
	window->draw(this->spriteBack);
	window->draw(this->spriteGround);
}
Map::~Map()
{
}

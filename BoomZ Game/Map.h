#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

class Map
{
public:
	sf::Sprite spriteGround, spriteBack;
public:

	Map(sf::RenderWindow *window);
	void update(int n);
	void draw();
	virtual ~Map();
private:
	int n;
	sf::RenderWindow *window;
	std::vector<sf::Texture> textureBack, textureGround;
};


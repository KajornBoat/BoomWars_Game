#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
class Enteryourname
{
public:
	sf::String yourname;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Font name_font;
	sf::Text name;
	bool checkEnter = true;
	void runEnter(bool chEnter);
	Enteryourname(sf::RenderWindow *window);
	sf::RenderWindow *windows;
	sf::Event event;
	~Enteryourname();
};



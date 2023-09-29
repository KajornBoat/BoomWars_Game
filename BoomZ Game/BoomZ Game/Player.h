#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Animation.h"


class Player
{
public:
	sf::Sprite sprite, Bullets;
	sf::Texture bullet;
	float myHP = 1500, myHP_max = 1500;
	float attack ;
	float defense;
	float power = 0;
	float power_max = 100;
	Animation *animation;

public:
	Player();
	void update(sf::View *view);
	void attacked(int attack);
	void heal(float hp);
	void powerUp(float power);
	void draw(sf::RenderWindow *window);
	void wear(int hat , int clothes , int bullet, bool checkRight = true);
	void clear();

	virtual ~Player();

private:
	
	struct playerType
	{
		sf::Texture tex;
		sf::Sprite sprite;
		int check = 555;
		bool state = false;
	};
	playerType Load[50];
	sf::Texture texture;

	float atk = 300;
	float def = 100;

	sf::Sprite bulletLoad[5];
	sf::Texture bulletTexLoad[5];
	sf::Text text,textAtk,textDef;
	sf::Font fonts[3];
	bool TexState = false;
	sf::Clock clock;
};


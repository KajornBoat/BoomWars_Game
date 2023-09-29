#pragma once
#include<SFML/Graphics.hpp>
#include <map>
#include<math.h>
#include<iostream>


class Collision
{
public:
	enum Check
	{
		Down, TopRight ,TopLeft
	};

public:

	static bool CollisionCheck( sf::Sprite *Object1, sf::Sprite *Object2,Check check, float *x = 0 ,float *y = 0,float *sloap = 0);
	static bool PixelPerfectTest(const sf::Sprite *Object1, const sf::Sprite *Object2, sf::Uint8 alphaLimit = 0);
	static bool CreateTextureAndBitmask(sf::Texture *LoadInto, const std::string Filename);
	virtual ~Collision();

private:
	class bitmaskmanager {

		virtual ~bitmaskmanager();
		sf::Uint8 getpixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y);
		sf::Uint8* getmask(const sf::Texture* tex);
		sf::Uint8* createmask(const sf::Texture* tex, const sf::Image& img);
	};
};


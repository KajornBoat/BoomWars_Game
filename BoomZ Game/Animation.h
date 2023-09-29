#pragma once
#include<SFML/Graphics.hpp>

class Animation
{
public:
	Animation(const sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
	void update(int rowImage, float deltaTime );

	~Animation();
public:
	sf::IntRect mRect;
	sf::Vector2u currentImage;
private:
	float totalTime;
	sf::Vector2u imageCount;
	float switchTime;
	int state;
};


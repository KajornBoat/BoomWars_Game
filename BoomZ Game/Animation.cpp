#include "Animation.h"

Animation::Animation(const sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	mRect.width = texture->getSize().x / float(imageCount.x);
	mRect.height = texture->getSize().y / float(imageCount.y);
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;
	this->state = state;
}

Animation::~Animation()
{
}

void Animation::update(int rowImage, float deltaTime) {

	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
			currentImage.x = 0;
		totalTime -= switchTime;
		//totalTime = 0;
	}
	currentImage.y = rowImage;
	mRect.left = currentImage.x*mRect.width;
	mRect.top = currentImage.y*mRect.height;
}

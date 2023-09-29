#include "Sprite.h"



Sprite::Sprite()
{
}

Sprite::UI::UI()
{
	this->scale.loadFromFile("Picture/common/scale.png");
	this->redNeedle.loadFromFile("Picture/common/redNeedle.png");
	this->redBar.loadFromFile("Picture/common/redBar.png");
	this->yellowBar.loadFromFile("Picture/common/yellowBar.png");
	this->hpbar.loadFromFile("Picture/common/HPbar.png");
	this->hp.loadFromFile("Picture/common/HPbarScale.png");
	this->power.loadFromFile("Picture/common/PowerbarScale.png");
	this->RedBar.setSize(sf::Vector2f(0, this->redBar.getSize().y));
	this->YellowBar.setSize(sf::Vector2f(0, this->yellowBar.getSize().y));
	this->HP.setSize(sf::Vector2f(0, this->hp.getSize().y));
	this->Power.setSize(sf::Vector2f(this->power.getSize().x, this->power.getSize().y));
	this->Scale.setTexture(scale);
	this->RedNeedle.setTexture(redNeedle);
	this->RedNeedle.setOrigin(sf::Vector2f(0, this->redNeedle.getSize().y / 2));
	this->RedBar.setTexture(&redBar);
	this->YellowBar.setTexture(&yellowBar);
	this->HPbar.setTexture(hpbar);
	this->HP.setTexture(&hp);
	this->Power.setTexture(&this->power);

	this->RedBarSize = this->redBar.getSize().x;
	this->YellowBarSize = this->yellowBar.getSize().x;
	this->hpSize = this->hp.getSize().x;
	this->PowerSize = this->power.getSize().x;

	this->fonts.loadFromFile("Fonts/Tahoma-Bold.ttf");
	this->TextAngle.setFillColor(sf::Color::Red);
	this->TextAngle.setCharacterSize(16);
	this->TextAngle.setFont(fonts);
}

void Sprite::UI::draw(sf::RenderWindow * window)
{
	window->draw(YellowBar);
	window->draw(RedBar);
	window->draw(Scale);
	window->draw(RedNeedle);
	window->draw(HPbar);
	window->draw(HP);
	window->draw(this->Power);
	window->draw(TextAngle);

}

void Sprite::UI::update(sf::View & view,int Angle)
{
	Scale.setPosition(sf::Vector2f(view.getCenter().x - 480, view.getCenter().y + 190));
	RedNeedle.setPosition(sf::Vector2f(view.getCenter().x - 432, view.getCenter().y + 238));
	RedBar.setPosition(sf::Vector2f(view.getCenter().x - 355, view.getCenter().y + 262));
	YellowBar.setPosition(sf::Vector2f(view.getCenter().x - 355, view.getCenter().y + 262));
	HPbar.setPosition(sf::Vector2f(view.getCenter().x - 485, view.getCenter().y - 292));
	HP.setPosition(sf::Vector2f(view.getCenter().x - 411, view.getCenter().y - 267));
	Power.setPosition(sf::Vector2f(view.getCenter().x - 417, view.getCenter().y - 283));
	TextAngle.setPosition(sf::Vector2f(view.getCenter().x - 443, view.getCenter().y+245));
	TextAngle.setString(std::to_string(Angle));
}

Sprite::Common::Common()
{
	this->point.loadFromFile("Picture/common/Point.png");
	this->Point.setTexture(this->point);
	this->Point.setPosition(sf::Vector2f(100.0f, 100.0f));
	this->Point.setOrigin((float)this->point.getSize().x / 2, (float)this->point.getSize().y / 2);

	this->bomb.loadFromFile("Picture/Bullet/bomb/bomb/381.png");
	this->Bomb.setTexture(this->bomb);
	this->Bomb.setOrigin(sf::Vector2f(this->bomb.getSize().x / 10, this->bomb.getSize().y / 10));
	this->BombAnimate = new Animation(&bomb, sf::Vector2u(5, 5), 0.04f);

	this->degree.loadFromFile("Picture/common/degree.png");
	this->Degree.setTexture(degree);
	this->Degree.setScale(0.7, 0.7);
	this->Degree.setOrigin(sf::Vector2f(-20, degree.getSize().y / 2));
	this->soundbuf.loadFromFile("Sound/play.ogg");
	this->playSound.setBuffer(soundbuf);

	this->bufstart.loadFromFile("Sound/start.ogg");
	this->bufdead.loadFromFile("Sound/dead.ogg");
	this->bufwin.loadFromFile("Sound/win.ogg");
	this->bufwalk.loadFromFile("Sound/walk.ogg");
	this->bufChart.loadFromFile("Sound/chart.ogg");
	this->bufShoot.loadFromFile("Sound/shoot.ogg");
	this->SoundStart.setBuffer(bufstart);
	this->SoundDead.setBuffer(bufdead);
	this->SoundWin.setBuffer(bufwin);
	this->SoundWalk.setBuffer(bufwalk);
	this->SoundChart.setBuffer(bufChart);
	this->SoundShoot.setBuffer(bufShoot);
}

void Sprite::Common::draw(sf::RenderWindow * window)
{
}


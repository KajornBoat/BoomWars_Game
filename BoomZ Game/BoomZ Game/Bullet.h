#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include "Collision.h"
#include"Player.h"
#include "Enemy.h"
#include"Item.h"


class Bullet
{
public:
	enum Side
	{
		Left,Right
	};
public:
	Bullet();
	Bullet(sf::Sprite *bullet ,sf::Sprite *Point, sf::Sprite *Bomb, float u , float angle ,float x , float y );
	void add(Bullet*,Side);
	void update();
	void shoot(float );
	void draw(sf::RenderWindow *window);
	void CoollisionCheck(sf::Sprite *Ground, Player *player ,Enemy::Dargon *enemy, Item *item,int ran,int *Score);
	virtual ~Bullet();
public:
	std::vector<Bullet> BulletLeft, BulletRight;
	sf::Sprite bullet , Bomb ;
	Animation *animationBullet;
private:
	void move(float n);
private:
	sf::Clock clock, AnimationTime , clockBomb , delayBomb;
	double PI = 3.1415926535897932384626433832795028841971693993;
	float u, angle , x, y;
	sf::Sprite Point;
	std::vector<std::pair<sf::Sprite* , sf::Sprite* > > vtSprite;
	Animation *BombAnimate;
	bool checkCollision = false;
	sf::Texture bulletTexLoad[5];
};


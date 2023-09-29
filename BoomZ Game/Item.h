#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"Collision.h"
#include"Player.h"
#include "Collision.h"
#include"Enemy.h"
#include"Player.h"




class Item
{
public:
	std::vector<sf::Sprite> SpriteBullet, SpriteClothes, SpriteHat, SpriteCommon;
	struct itemDropType
	{ 
		sf::Sprite sprite,PointStr;
		int kind;
		int type;
	};
	struct itemTableType
	{
		bool state = false;
		sf::Sprite sprite;
		int Type;
	};
	std::vector<itemDropType> itemDrop;
	itemTableType itemHatTable[4];
	itemTableType itemClothesTable[4];
	itemTableType itemBulletTable[5];

	int itemHatType = 0, itemClothesType = 0, itemBulletType = 0;
	Player *player;
	itemTableType itemTable[6];

	sf::Sprite Bomb;
	Animation *BombAnimate;
public:
	Item(Player *player,  sf::Sprite *Bomb);
	void update(sf::Sprite *ground, sf::View *view);
	void draw(sf::RenderWindow *window);
	void add(int n, sf::Vector2f position);
	void use(Player *player , Enemy::Dargon *enemy, sf::View *view,int ran, bool *checkRight,int *score);
	void keep(Player *player);
	void clear();

	virtual ~Item();
private:
	sf::Sprite Point;
	sf::Texture point;
	std::vector<sf::Texture> TextureBullet, TextureClothes, TextureHat, TextureCommon;
	sf::Texture talbe,clothesTable, clothesTableBotton , talbeBotton;
	sf::Sprite Table, ClothesTable, ClothesTableBotton, TalbeBotton;
	bool lastState[12];
	int type;

	int countBullet[5] = {-10,-10,-10,-10,-10};
	int countClothes[4] = { -10 ,-10,-10,-10 };
	int countHat[3] = { -10 ,-10,-10 };

	sf::Clock clockBomb, delayBomb;

	sf::SoundBuffer bufWear, bufitem;
	sf::Sound SoundWear, SoundItem;

};


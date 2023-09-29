#pragma once
#include <SFML/Graphics.hpp>
#include"Animation.h"
#include<iostream>
#include"Player.h"


class Enemy
{
	public:
		class Dargon
		{
		public:
			Dargon();
			Dargon(Player *player);
			Dargon(int n,float hp , float attack = 100, int rand = 100);
			void add(Dargon *enemy);
			void update();
			void move();
			void attack();
			void attacked(int n);
			void textPrint(int n,sf::Vector2f position);
			void draw(sf::RenderWindow *window);
		public:
			sf::Sprite sprite, Point;
			std::vector<Dargon> enemy;
			float enemyHP = 100, enemyHP_max = 100;
			float Attack;
			sf::Clock AnimationTime;

		private:
			int n = 1;
			Player *player;
			sf::Texture texture, point;
			sf::Clock attackTime, delay;
			Animation *animation;

			sf::Texture textureHp, textureHpBar;
			sf::RectangleShape spriteHp;
			sf::Sprite spriteHpBar;
			float spriteHpSize;

	
			sf::Font fonts;
			struct textType
			{
				sf::Text text;
				sf::Clock clock;
			};
			std::vector<textType> text;
			textType TextLoad;
		
		};

};


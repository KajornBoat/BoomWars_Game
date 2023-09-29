#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<stdio.h>
#include"Animation.h"
#include"Collision.h"
#include"Bullet.h"
#include"Player.h"
#include"Map.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Menu.h"
#include"Item.h"



#define speed 1.0f 
double PI = 3.1415926535897932384626433832795028841971693993;

int main()
{
	/*---------------------------------SetUp----------------------------------------*/

	sf::RenderWindow window(sf::VideoMode(1400, 850), "Bomb Wars", sf::Style::Close |sf::Style::Titlebar);
	sf::View view(sf::FloatRect(0,200,980,595));
	window.setFramerateLimit(60);
	srand(time(NULL));

	bool checkLeft = false, checkRight = true, checkStandStart = false, checkMoveDown = true, PositiveScale = true, checkStart = true, lastspace = false ;
	float u = 0,u_max = 700 , x = speed, y;
	float angle = 45, theta = 0 , angleOfGround , shootingAngle, slop;
	int CheckShootStart = 2;
	long float deltaTimeAnimation = 0.0f, detaBoom = 0.0f, Delay;
	int Score = 0,curentState = 1 ;

	sf::Event event;
	sf::Clock delay, clockAnimation, clockTime,delaywalk;
	std::string strShowScore;
	sf::Text ShowScore;
	Bullet bullet;
	Player player;
	Map map(&window);
	Sprite::Common common;
	Sprite::UI ui;
	Enemy::Dargon enemy(&player);
	Menu menu(&window,&Score);
	Item item(&player,&common.Bomb);

	map.update(1);
	/*-------------------------------------------------------------------------------*/
	while (window.isOpen())
	{
		menu.run();
		if (!menu.menucheck and checkStart)
		{
			common.SoundStart.play();
			common.playSound.play();
			common.playSound.setLoop(10);
			delay.restart();
			clockAnimation.restart();
			enemy.AnimationTime.restart();
			checkStart = false;
			strShowScore = menu.enterName->yourname;
			strShowScore += " Score : ";
			ShowScore = menu.enterName->name;
			ShowScore.setFillColor(sf::Color::Red);
			ShowScore.setCharacterSize(30);
			ShowScore.setOutlineColor(sf::Color::White);
			ShowScore.setOutlineThickness(3);
			clockTime.restart();
		}
		
		ShowScore.setString(strShowScore + std::to_string(Score));
		ShowScore.setOrigin(sf::Vector2f(ShowScore.getGlobalBounds().width / 2, 0));

		Enemy::Dargon m(curentState,300 + (330*(curentState-1)), 300+((curentState-1)*50), rand());
		if (clockTime.getElapsedTime().asSeconds() < 60 )
		{
			enemy.add(&m);
		}
		else if (common.Point.getPosition().x>1350 && enemy.enemy.size() == 0)
		{
			curentState++;
			clockTime.restart();
			if (curentState != 4 )
			{
				map.update(curentState);
				common.SoundStart.play();
			}
			common.Point.setPosition(sf::Vector2f(100.0f, 150.0f));
			checkMoveDown = true;
			view.setCenter((view.getSize().x / 2), 497.5);
			item.itemDrop.clear();
		}
		else if (enemy.enemy.size() == 0 && curentState == 3 )
		{
			std::cout << "YOUR ARE WINER\n";
		}
		if (curentState == 4)
		{
			common.SoundWin.play();
			menu.Overcheck = true;
			menu.menucheck = true;
			curentState = 1;
			map.update(curentState);
			common.Point.setPosition(sf::Vector2f(100.0f, 150.0f));
			checkMoveDown = true;
			view.setCenter((view.getSize().x / 2), 450);
			checkStart = true;
			player.clear();
			enemy.enemy.clear();
			item.clear();
			menu.Bonus = Score/4;
			menu.Text();
			common.playSound.stop();
			ui.RedBar.setSize(sf::Vector2f(0, ui.RedBar.getSize().y));
			player.wear(0, 0, 0);
		}


		deltaTimeAnimation = clockAnimation.restart().asSeconds();
		Delay = delay.getElapsedTime().asSeconds();
		player.animation->update(2, deltaTimeAnimation);
		
		if (Collision::CollisionCheck(&common.Point, &map.spriteGround,Collision::Check::Down)){
			checkMoveDown = false;
		} 
		if (checkMoveDown) {
			common.Point.move(0.0f, speed*2);
			Delay = 2;
			player.animation->update(1, deltaTimeAnimation);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 20 ) ) && Delay >= 0.7)
		{
			if (!checkMoveDown)
			{
				player.animation->update(0, deltaTimeAnimation);
				if (delaywalk.getElapsedTime().asSeconds() > 0.4)
				{
					common.SoundWalk.play();
					delaywalk.restart();
				}
			}     

			if (!checkRight)
			{
				player.sprite.scale(-1.0f, 1.0f);
				common.Degree.scale(-1.0f,1.0f);
				checkLeft = false;
				checkRight = true;
			}
			if ((Collision::CollisionCheck(&common.Point, &map.spriteGround, Collision::Check::TopRight, &x, &y,&slop ))&& player.sprite.getPosition().x + 35 <= window.getSize().x)
			{
				common.Point.move(x, y);
				theta = (slop * 180) / PI;
				if (fabsf(theta) > 7) {
					player.sprite.setRotation(theta);
				}
				else if (fabsf(theta) <= 3) player.sprite.setRotation(0);
			}
			else if(player.sprite.getPosition().x + 35  <= window.getSize().x)
			{

				common.Point.move(speed * 2, 0.0f);
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -85))&& Delay >= 0.7)
		{
			if (!checkMoveDown)
			{
				player.animation->update(0, deltaTimeAnimation);
				if (delaywalk.getElapsedTime().asSeconds() > 0.4)
				{
					common.SoundWalk.play();
					delaywalk.restart();
				}

			}
			
			if (!checkLeft)
			{
				player.sprite.scale(-1.0f,1.0f);
				common.Degree.scale(-1.0f, 1.0f);
				checkLeft = true;
				checkRight = false;
			}
			if (Collision::CollisionCheck(&common.Point, &map.spriteGround, Collision::Check::TopLeft, &x, &y, &slop) && player.sprite.getPosition().x - 35 >= 0 )
			{
				common.Point.move(-x, -y);
				theta = (slop * 180) / PI;
				if (fabsf(theta) > 10) {
					player.sprite.setRotation(theta);
				}
				else if (fabsf(theta) <= 3) player.sprite.setRotation(0);
			}
			else if(player.sprite.getPosition().x - 35 >= 0)
			{
				common.Point.move(-speed * 2, 0.0f);
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) or sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -80) &&(angle <=80) && Delay >= 0.7)
		{
			angle += speed;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 20)) && (angle >=0) && Delay >= 0.7)
		{
			angle -= speed;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) or sf::Joystick::isButtonPressed(0,0))&& Delay >= 0.7)
		{
			if (u <= 0) PositiveScale = true;
			else if (u >= u_max) PositiveScale = false;
			if (PositiveScale) u += 6*speed;
			else u -= 6*speed;
			CheckShootStart = 0;
			ui.YellowBar.setSize(sf::Vector2f((u*ui.YellowBarSize)/u_max, ui.YellowBar.getSize().y));
			if (!lastspace)
			{
				common.SoundChart.play();
				common.SoundChart.setLoop(10);
				lastspace = true;
			}
				
		
		}
		else { CheckShootStart++; }
		if (CheckShootStart == 1 )
		{
			lastspace = false;
			common.SoundChart.stop();
			common.SoundShoot.play();
			checkStandStart = true;
			delay.restart().asSeconds();
			player.animation->currentImage.x = 0;
			Bullet b(&player.Bullets, &common.Point, &common.Bomb, u, shootingAngle, common.Point.getPosition().x, common.Point.getPosition().y);
			if(checkLeft) bullet.add(&b, Bullet::Side::Left);
			else if (checkRight) bullet.add(&b, Bullet::Side::Right);

			ui.YellowBar.setSize(sf::Vector2f( 0 , ui.YellowBar.getSize().y));
			ui.RedBar.setSize(sf::Vector2f((u*ui.RedBarSize) / u_max, ui.RedBar.getSize().y));
			u = 0;
		}
		if (Delay <= 0.7&&checkStandStart) {
			deltaTimeAnimation = clockAnimation.restart().asSeconds();
			player.animation->update(3, deltaTimeAnimation);
		}

		if (checkRight) {
			common.Degree.setPosition(sf::Vector2f(common.Point.getPosition().x + 20, common.Point.getPosition().y - 30));
			angleOfGround = -(360 - player.sprite.getRotation()) - angle;
			shootingAngle = angle + (360 - player.sprite.getRotation());
			ui.RedNeedle.setRotation(-shootingAngle);
		}
		else if(checkLeft) {
			common.Degree.setPosition(sf::Vector2f(common.Point.getPosition().x - 20, common.Point.getPosition().y - 30));
			angleOfGround = player.sprite.getRotation() + angle;
			shootingAngle = player.sprite.getRotation() + angle;
			ui.RedNeedle.setRotation(180+shootingAngle);
		}

		if (shootingAngle > 180) shootingAngle -= 360;
		player.sprite.setPosition(sf::Vector2f(common.Point.getPosition().x, (common.Point.getPosition().y)));
		common.Degree.setRotation(angleOfGround);

		bullet.update();
		bullet.CoollisionCheck(&map.spriteGround,&player,&enemy, &item,rand(),&Score);
	
		if (player.sprite.getPosition().x-(view.getSize().x/2)>=0 && player.sprite.getPosition().x + (view.getSize().x /2) <= window.getSize().x)
		{
			view.setCenter(player.sprite.getPosition().x,497.5);
		}
		ui.update(view, shootingAngle);
		ui.HP.setSize(sf::Vector2f((player.myHP*ui.hpSize) / player.myHP_max, ui.HP.getSize().y));
		ui.Power.setSize(sf::Vector2f((player.power*ui.PowerSize) / player.power_max, ui.Power.getSize().y));

		player.update(&view);
		ShowScore.setPosition(sf::Vector2f(view.getCenter().x+65, view.getCenter().y-275));

		enemy.move();
		enemy.attack();

		item.update(&map.spriteGround,&view);
		item.use(&player,&enemy,&view ,rand(),&checkRight,&Score);
		item.keep(&player);

		if (!menu.menucheck)
		{
			window.setView(view);
		}
/*-------------------------------Display---------------------------------------*/
		window.clear();
		
		map.draw();
		enemy.draw(&window);
		player.sprite.setTextureRect(player.animation->mRect);
		window.draw(player.sprite);
		if(Delay >= 0.7)
		window.draw(common.Degree);
		bullet.draw(&window);
		item.draw(&window);

		ui.draw(&window);
		player.draw(&window);

		window.draw(ShowScore);

		window.display();
/*-------------------------------------------------------------------------------*/
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		{
			window.close();
		}
		if (player.myHP <= 0)
		{
			common.SoundDead.play();
			menu.Overcheck = true;
			menu.menucheck = true;
			curentState = 1;
			map.update(curentState);
			common.Point.setPosition(sf::Vector2f(100.0f, 150.0f));
			checkMoveDown = true;
			view.setCenter((view.getSize().x / 2), 450);
			checkStart = true;
			player.clear();
			item.clear();
			enemy.enemy.clear();
			menu.Text();
			common.playSound.stop();
			player.wear(0, 0, 0);
			ui.RedBar.setSize(sf::Vector2f(0, ui.RedBar.getSize().y));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			player.attacked(99999);
		}
	}
	return 0;
}
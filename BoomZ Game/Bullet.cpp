#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Sprite *bullet, sf::Sprite *Point, sf::Sprite *Bomb, float u, float angle ,float x, float y)
{
	this->bullet = *bullet;
	this->angle = angle;
	this->u = u;
	this->x = x;
	this->y = y;
	this->animationBullet = new Animation(this->bullet.getTexture(), sf::Vector2u(25, 1), 0.02f);
	this->Point = *Point;
	this->Point.setPosition(x,y);

	this->Bomb = *Bomb;
	this->Bomb.setOrigin(sf::Vector2f(this->Bomb.getTexture()->getSize().x / 10, this->Bomb.getTexture()->getSize().y / 10));
	this->BombAnimate = new Animation(Bomb->getTexture(), sf::Vector2u(5, 5), 0.04f);

		
}
void Bullet::add(Bullet *bullet, Side side)
{
	if(side == Right)
	{
		this->BulletRight.push_back(*bullet);
	}
	if (side == Left) 
	{
		this->BulletLeft.push_back(*bullet);
	}
}
void Bullet::update()
{
	for (int i = 0; i < BulletRight.size() ; i++)
	{
		this->BulletRight[i].move(1);
		this->BulletRight[i].BombAnimate->update(4, this->BulletRight[i].clockBomb.restart().asSeconds());
	}
	for (int i = 0; i < BulletLeft.size(); i++)
	{
		this->BulletLeft[i].move(-1);
		this->BulletLeft[i].BombAnimate->update(4, this->BulletLeft[i].clockBomb.restart().asSeconds());
	}
}
void Bullet::move(float n)
{
	float deltaTimeAnimation = AnimationTime.restart().asSeconds();
	animationBullet->update(0, deltaTimeAnimation);
	float deltaTime = 2 * clock.getElapsedTime().asSeconds();

	float X = x - (n*15) + n*(cosf((angle*PI) / 180)*u * deltaTime);
	float Y = y - (20) - ((sinf((angle*PI) / 180)*u*deltaTime) - (0.5*200*powf(deltaTime, 2)));

	this->bullet.setPosition(X,Y);
	this->Point.setPosition(X,Y);
}

void Bullet::draw(sf::RenderWindow *window)
{
	for (int i = 0; i < BulletRight.size(); i++)
	{
		if (!BulletRight[i].checkCollision)
		{
			this->BulletRight[i].bullet.setTextureRect(BulletRight[i].animationBullet->mRect);
			window->draw(BulletRight[i].bullet);
		}
		else
		{
			if (BulletRight[i].delayBomb.getElapsedTime().asSeconds() < 0.18)
			{
				BulletRight[i].Bomb.setTextureRect(BulletRight[i].BombAnimate->mRect);
				window->draw(BulletRight[i].Bomb);
			}
			else if (BulletRight[i].checkCollision)
			{
				BulletRight.erase(BulletRight.begin() + i);
			}
		}
		
	}

	for (int i = 0; i < BulletLeft.size(); i++)
	{
		if (!BulletLeft[i].checkCollision)
		{
			this->BulletLeft[i].bullet.setTextureRect(BulletLeft[i].animationBullet->mRect);
			window->draw(BulletLeft[i].bullet);
		}
		else
		{
			if (BulletLeft[i].delayBomb.getElapsedTime().asSeconds() < 0.18)
			{
				BulletLeft[i].Bomb.setTextureRect(BulletLeft[i].BombAnimate->mRect);
				window->draw(BulletLeft[i].Bomb);
			}
			else if (BulletLeft[i].checkCollision)
			{
				BulletLeft.erase(BulletLeft.begin() + i);
			}
		}
	}
	
}

void Bullet::CoollisionCheck(sf::Sprite *Ground, Player *player, Enemy::Dargon *enemy, Item *item,int ran,int *Score)
{
		for (int i = 0; i < BulletRight.size(); i++)
		{
			if ((Collision::PixelPerfectTest(&BulletRight[i].Point, Ground) ) && !BulletRight[i].checkCollision)
			{
				if (fabs(BulletRight[i].Point.getPosition().x - player->sprite.getPosition().x <= 30 and fabs(BulletRight[i].Point.getPosition().y - player->sprite.getPosition().y) <= 40))
				{
					player->attacked(player->attack);
				}
				BulletRight[i].checkCollision = true;
				BulletRight[i].Bomb.setPosition(BulletRight[i].Point.getPosition());
				BulletRight[i].BombAnimate->currentImage.x = 0;
				BulletRight[i].delayBomb.restart().asSeconds();
			}
			for (int n = 0; n < enemy->enemy.size(); n++)
			{
				if (Collision::PixelPerfectTest(&BulletRight[i].bullet, &enemy->enemy[n].sprite) && !BulletRight[i].checkCollision)
				{
					enemy->enemy[n].attacked(player->attack);
					enemy->textPrint(player->attack, { enemy->enemy[n].sprite.getPosition().x , enemy->enemy[n].sprite.getPosition().y });
					if (enemy->enemy[n].enemyHP <= 0)
					{
						item->add(ran, enemy->enemy[n].sprite.getPosition());
						enemy->enemy.erase(enemy->enemy.begin() + n);
						*Score += 1;
		
					}
					BulletRight[i].checkCollision = true;
					BulletRight[i].Bomb.setPosition(BulletRight[i].Point.getPosition());
					BulletRight[i].BombAnimate->currentImage.x = 0;
					BulletRight[i].delayBomb.restart().asSeconds();
				}
			}
		}
		for (int i = 0; i < BulletLeft.size(); i++)
		{
			if ((Collision::PixelPerfectTest(&BulletLeft[i].Point, Ground) ) && !BulletLeft[i].checkCollision)
			{
				if (fabs(BulletLeft[i].Point.getPosition().x - player->sprite.getPosition().x) <= 30 and fabs(BulletLeft[i].Point.getPosition().y - player->sprite.getPosition().y) <= 40)
				{
					player->attacked(player->attack);
				}
				BulletLeft[i].checkCollision = true;
				BulletLeft[i].Bomb.setPosition(BulletLeft[i].Point.getPosition());
				BulletLeft[i].BombAnimate->currentImage.x = 0;
				BulletLeft[i].delayBomb.restart().asSeconds();
			}
			for (int n = 0; n < enemy->enemy.size(); n++)
			{
				if (Collision::PixelPerfectTest(&BulletLeft[i].Point, &enemy->enemy[n].sprite) && !BulletLeft[i].checkCollision)
				{
					enemy->enemy[n].attacked(player->attack);
					enemy->textPrint(player->attack, { enemy->enemy[n].sprite.getPosition().x , enemy->enemy[n].sprite.getPosition().y });
					if (enemy->enemy[n].enemyHP <= 0)
					{
						item->add(ran, enemy->enemy[n].sprite.getPosition());
						enemy->enemy.erase(enemy->enemy.begin() + n);
						*Score += 1;
						
					}
					BulletLeft[i].checkCollision = true;
					BulletLeft[i].Bomb.setPosition(BulletLeft[i].Point.getPosition());
					BulletLeft[i].BombAnimate->currentImage.x = 0;
					BulletLeft[i].delayBomb.restart().asSeconds();
				}
			}
		}
}

Bullet::~Bullet()
{
}

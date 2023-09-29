
#include "Enemy.h"


Enemy::Dargon::Dargon()
{
	
}
Enemy::Dargon::Dargon(Player * player)
{
	this->player = player;
	fonts.loadFromFile("Fonts/Tahoma-Bold.ttf");
	TextLoad.text.setCharacterSize(16);
	TextLoad.text.setFont(fonts);
}

Enemy::Dargon::Dargon(int n , float hp , float attack,int random)
{
	char file = '0' + n;
	std::string FileAddress = "Picture/Enemy/";
	FileAddress += file;
	this->texture.loadFromFile(FileAddress + ".png");
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(sf::Vector2f((float)this->texture.getSize().x/6, (float)this->texture.getSize().y/4));
	this->animation = new Animation(&this->texture, sf::Vector2u(3, 4), 0.1f);
	this->Attack = attack;
	this->point.loadFromFile("Picture/common/Point.png");
	this->Point.setTexture(this->point);
	this->Point.setPosition(sf::Vector2f(random%1000 + 1, 200.0f));

	this->Point.setOrigin((float)this->point.getSize().x / 2, (float)this->point.getSize().y / 2);
	this->enemyHP = hp;
	this->enemyHP_max = hp;

	this->textureHp.loadFromFile("Picture/common/enemyHP.png");
	this->textureHpBar.loadFromFile("Picture/common/enemyHPbar.png");
	this->spriteHp.setTexture(&this->textureHp);
	this->spriteHpBar.setTexture(this->textureHpBar);
	this->spriteHp.setSize(sf::Vector2f(this->textureHp.getSize().x, this->textureHp.getSize().y));
	this->spriteHpSize = textureHp.getSize().x;
}

void Enemy::Dargon::add(Dargon * enemy)
{
	if (this->delay.getElapsedTime().asSeconds() > 1.5 && this->enemy.size() < 10)
	{
		this->enemy.push_back(*enemy);
		this->delay.restart().asSeconds();
	}
}

void Enemy::Dargon::update()
{
	float deltaTimeAnimation = AnimationTime.restart().asSeconds();
	for (int i = 0; i < enemy.size(); i++)
	{
		this->enemy[i].animation->update(this->enemy[i].n, deltaTimeAnimation);
		this->enemy[i].sprite.setPosition(sf::Vector2f(this->enemy[i].Point.getPosition().x, this->enemy[i].Point.getPosition().y));
	}

}

void Enemy::Dargon::move()
{
	float deltaTimeAnimation = AnimationTime.restart().asSeconds();
	for (int i = 0; i < enemy.size(); i++)
	{
		this->enemy[i].animation->update(this->enemy[i].n, deltaTimeAnimation);
		this->enemy[i].sprite.setPosition(sf::Vector2f(this->enemy[i].Point.getPosition().x, this->enemy[i].Point.getPosition().y));
		this->enemy[i].spriteHpBar.setPosition(sf::Vector2f(this->enemy[i].Point.getPosition().x - (enemy[i].textureHp.getSize().x/2), this->enemy[i].Point.getPosition().y-125));
		this->enemy[i].spriteHp.setPosition(sf::Vector2f(this->enemy[i].Point.getPosition().x - (enemy[i].textureHp.getSize().x/2) + 3, this->enemy[i].Point.getPosition().y-125+1));
		this->enemy[i].spriteHp.setSize(sf::Vector2f((enemy[i].enemyHP * enemy[i].spriteHpSize) / enemy[i].enemyHP_max, enemy[i].textureHp.getSize().y));
	}
	for (int i = 0; i < enemy.size(); i++)
	{

		if (this->player->sprite.getPosition().x - this->enemy[i].Point.getPosition().x >= 20)
		{
			this->enemy[i].Point.move(0.3, 0);
			this->enemy[i].n = 1;
		}
		else if (this->player->sprite.getPosition().x - this->enemy[i].Point.getPosition().x <= -20)
		{
			this->enemy[i].Point.move(-0.3, 0);
			this->enemy[i].n = 3;
		}
		else
		{
			this->enemy[i].n = 2;

		}
		if (this->player->sprite.getPosition().y - this->enemy[i].Point.getPosition().y >= 15)
		{
			this->enemy[i].Point.move(0, 0.3);
		}
		else  {
			this->enemy[i].Point.move(0, -0.3);
		}
	}
}

void Enemy::Dargon::attack()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (attackTime.getElapsedTime().asSeconds() > 0.5)
		{
			if (this->player->sprite.getPosition().x - this->enemy[i].Point.getPosition().x <= 21 && this->player->sprite.getPosition().x - this->enemy[i].Point.getPosition().x >= -21 && this->player->sprite.getPosition().y - this->enemy[i].Point.getPosition().y <= 16)
				{
					player->attacked(this->enemy[i].Attack);
				}
			attackTime.restart().asSeconds();
		}
	}

}

void Enemy::Dargon::attacked(int n)
{
	enemyHP -= n ;

}

void Enemy::Dargon::textPrint(int n, sf::Vector2f position)
{
	TextLoad.text.setString("-" + std::to_string(n));
	TextLoad.text.setFillColor(sf::Color::Red);
	TextLoad.text.setPosition(sf::Vector2f(position.x - 13, position.y - 150));
	TextLoad.clock.restart();
	text.push_back(TextLoad);
}

void Enemy::Dargon::draw(sf::RenderWindow * window)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		this->enemy[i].sprite.setTextureRect(this->enemy[i].animation->mRect);
		window->draw(this->enemy[i].sprite);
		window->draw(this->enemy[i].spriteHpBar);
		window->draw(this->enemy[i].spriteHp);

	}

	for (int i = 0 ; i < text.size() ; i++)
	{
		if (text[i].clock.getElapsedTime().asSeconds() < 0.5)
		{
			window->draw(text[i].text);
		}
		else
		{
			text.erase(text.begin() + i);
			i--;
		}
	}

}
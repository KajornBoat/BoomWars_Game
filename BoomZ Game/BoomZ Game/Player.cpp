#include "Player.h"


Player::Player()
{
	this->texture.loadFromFile("Picture/Player/111.png");
	this->sprite.setTexture(this->texture);
	this->animation = new Animation(&this->texture, sf::Vector2u(40, 4), 0.1f);
	this->sprite.setScale(0.7, 0.7);
	this->sprite.setOrigin(sf::Vector2f(115.0f, 125.0f));
	this->bullet.loadFromFile("Picture/Bullet/0.png");
	this->Bullets.setTexture(bullet);
	this->Bullets.setScale(0.7,0.7);
	this->Bullets.setOrigin(sf::Vector2f((bullet.getSize().x / 25) / 2, bullet.getSize().y / 2.0f));
	fonts[0].loadFromFile("Fonts/Tahoma-Bold.ttf");
	fonts[1].loadFromFile("Fonts/Superspace Bold ver 1.00.ttf");
	fonts[2].loadFromFile("Fonts/Superspace Regular ver 1.00.ttf");
	textAtk.setCharacterSize(18);
	textDef.setCharacterSize(18);
	textAtk.setFillColor(sf::Color::Red);
	textDef.setFillColor(sf::Color::Red);
	textAtk.setFont(fonts[1]);
	textDef.setFont(fonts[1]);

	for (int i = 0; i < 5; i++)
	{
		char n = '0' + i;
		std::string Fileadress = "Picture/Bullet/";
		Fileadress += n;
		bulletTexLoad[i].loadFromFile(Fileadress + ".png");
		bulletLoad[i].setTexture(bulletTexLoad[i]);
		bulletLoad[i].setScale(0.7, 0.7);
		bulletLoad[i].setOrigin(sf::Vector2f((bulletTexLoad[i].getSize().x / 25) / 2, bulletTexLoad[i].getSize().y / 2.0f));
	}
}

void Player::update(sf::View *view)
{
	textAtk.setString("Atk : " + std::to_string((int)attack));
	textDef.setString("Def : " + std::to_string((int)defense));
	textAtk.setPosition(sf::Vector2f(view->getCenter().x-365, view->getCenter().y-247));
	textDef.setPosition(sf::Vector2f(view->getCenter().x-285, view->getCenter().y - 247));
}
void Player::attacked(int attack)
{
	myHP -= attack - defense;
	if (myHP < 0) myHP = 0;
	else
	{
		text.setString("-" + std::to_string((int)attack - (int)defense));
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(16);
		text.setFont(fonts[0]);
		text.setPosition(sf::Vector2f(this->sprite.getPosition().x - 13, this->sprite.getPosition().y + 13));
		TexState = true;
		clock.restart();
	}
}

void Player::heal(float hp)
{
	this->myHP += hp;
	if (myHP > myHP_max)
	{
		myHP = myHP_max;
	}
	text.setString("+" + std::to_string((int)hp ));
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(16);
	text.setFont(fonts[0]);
	text.setPosition(sf::Vector2f(this->sprite.getPosition().x - 13, this->sprite.getPosition().y + 13));
	TexState = true;
	clock.restart();
}

void Player::powerUp(float power)
{
	this->power += power;
	if (this->power > power_max)
	{
		this->power = power_max;
	}
}

void Player::draw(sf::RenderWindow * window)
{
	if (TexState)
	{
		window->draw(text);
	}
	if (clock.getElapsedTime().asSeconds()>0.5)
	{
		clock.restart();
		TexState = false;
	}
	window->draw(textAtk);
	window->draw(textDef);
}

void Player::wear(int hat, int clothes, int bullet , bool checkRight)
{
	char file1 = '0' + hat, file2 = '0' + clothes, file3 = '0' + bullet;
	int check = (9*1000)+(hat * 100) + (clothes * 10) + bullet;

	attack = atk + (bullet * 60);
	defense = (def + (clothes * 20)) + (hat * 15);


	std::string FileAddress = "Picture/Player/";
	FileAddress += file1;
	FileAddress += file2;
	FileAddress += file3;
	for (int i = 0 ; i < 45 ; i++)
	{
		if (Load[i].check != check and !Load[i].state) {
			Load[i].tex.loadFromFile(FileAddress + ".png");
			Load[i].sprite.setTexture(Load[i].tex);
			Load[i].check = check;
			if (checkRight)
			{
				Load[i].sprite.setScale(0.7, 0.7);
			}
			else
			{
				Load[i].sprite.setScale(-0.7, 0.7);
			}
			Load[i].sprite.setOrigin(sf::Vector2f(115.0f, 125.0f));
			this->animation = new Animation(&this->Load[i].tex, sf::Vector2u(40, 4), 0.1f);
			this->sprite = Load[i].sprite;
			Load[i].state = true;

			this->Bullets = bulletLoad[bullet];

			break;
		}
		if (Load[i].check == check)
		{
			if (checkRight)
			{
				Load[i].sprite.setScale(0.7, 0.7);
			}
			else
			{
				Load[i].sprite.setScale(-0.7, 0.7);
			}
			this->sprite = Load[i].sprite;
			this->Bullets = bulletLoad[bullet];
			break;
		}
	}
}

void Player::clear()
{
	myHP = 1500;
	power = 0;
}

Player::~Player()
{
}

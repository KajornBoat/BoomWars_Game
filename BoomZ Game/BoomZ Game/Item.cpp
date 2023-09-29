#include "Item.h"


Item::Item(Player *player, sf::Sprite *Bomb)
{
	this->player = player;
	sf::Texture texBullet[5];
	sf::Sprite sptiteBullet[5];
	TextureBullet.push_back(texBullet[0]);
	TextureBullet.push_back(texBullet[1]);
	TextureBullet.push_back(texBullet[2]);
	TextureBullet.push_back(texBullet[3]);
	TextureBullet.push_back(texBullet[4]);
	for (int i = 0; i < 5; i++)
	{
		char file = '0' + i + 1;
		std::string FileAddress = "Picture/Items/bullet/";
		FileAddress += file;
		TextureBullet[i].loadFromFile(FileAddress + ".png");
		sptiteBullet[i].setTexture(TextureBullet[i]);
		sptiteBullet[i].setOrigin(sf::Vector2f(TextureBullet[i].getSize().x / 2, TextureBullet[i].getSize().y /2));
		sptiteBullet[i].setScale(0.7, 0.7);
		SpriteBullet.push_back(sptiteBullet[i]);
	}


	sf::Texture texClothes[4];
	sf::Sprite sptiteClothes[4];
	TextureClothes.push_back(texClothes[0]);
	TextureClothes.push_back(texClothes[1]);
	TextureClothes.push_back(texClothes[2]);
	TextureClothes.push_back(texClothes[3]);
	for (int i = 0; i < 4; i++)
	{
		char file = '0' + i + 1;
		std::string FileAddress = "Picture/Items/clothes/";
		FileAddress += file;
		TextureClothes[i].loadFromFile(FileAddress + ".png");
		sptiteClothes[i].setTexture(TextureClothes[i]);
		sptiteClothes[i].setOrigin(sf::Vector2f(TextureClothes[i].getSize().x / 2, TextureClothes[i].getSize().y /2));
		sptiteClothes[i].setScale(0.7, 0.7);
		SpriteClothes.push_back(sptiteClothes[i]);
	}


	sf::Texture texCommon[2];
	sf::Sprite sptiteCommon[2];
	TextureCommon.push_back(texCommon[0]);
	TextureCommon.push_back(texCommon[1]);
	
	for (int i = 0 ; i < 2 ; i++)
	{
		char file = '0' + i+1;
		std::string FileAddress = "Picture/Items/common/";
		FileAddress += file;
		TextureCommon[i].loadFromFile(FileAddress + ".png");
		sptiteCommon[i].setTexture(TextureCommon[i]);
		sptiteCommon[i].setOrigin(sf::Vector2f(TextureCommon[i].getSize().x / 2, TextureCommon[i].getSize().y / 2));
		sptiteCommon[i].setScale(0.7, 0.7);
		SpriteCommon.push_back(sptiteCommon[i]);
	}


	sf::Texture texHat[3];
	sf::Sprite sptiteHat[3];
	TextureHat.push_back(texHat[0]);
	TextureHat.push_back(texHat[1]);
	TextureHat.push_back(texHat[2]);
	for (int i = 0; i < 3; i++)
	{
		char file = '0' + i + 1;
		std::string FileAddress = "Picture/Items/hat/";
		FileAddress += file;
		TextureHat[i].loadFromFile(FileAddress + ".png");
		sptiteHat[i].setTexture(TextureHat[i]);
		sptiteHat[i].setOrigin(sf::Vector2f(TextureHat[i].getSize().x / 2, TextureHat[i].getSize().y /2));
		sptiteHat[i].setScale(0.7, 0.7);
		SpriteHat.push_back(sptiteHat[i]);
	}

	point.loadFromFile("Picture/common/Point.png");
	Point.setTexture(point);
	talbe.loadFromFile("Picture/Items/table/table.png");
	Table.setTexture(talbe);
	Table.setScale(0.7,0.7);
	clothesTable.loadFromFile("Picture/Items/table/clothesTable.png");
	ClothesTable.setTexture(clothesTable);
	ClothesTable.setScale(0.7, 0.7);
	clothesTableBotton.loadFromFile("Picture/Items/table/clothesTableBotton.png");
	ClothesTableBotton.setTexture(clothesTableBotton);
	ClothesTableBotton.setScale(0.7, 0.7);
	talbeBotton.loadFromFile("Picture/Items/table/tableBotton.png");
	TalbeBotton.setTexture(talbeBotton);
	TalbeBotton.setScale(0.7, 0.7);

	itemBulletTable[0].sprite = SpriteBullet[0];
	itemBulletTable[0].Type = 0;
	itemBulletTable[0].state = true;
	countBullet[0] = 0;

	itemHatTable[0].sprite = SpriteHat[0];
	itemHatTable[0].state = true;
	itemHatTable[0].Type = 0;
	countHat[0] = 0;

	itemClothesTable[0].sprite = SpriteClothes[0];
	itemClothesTable[0].state = true;
	itemClothesTable[0].Type = 0;
	countClothes[0] = 0;

	player->wear(0, 0, 0);

	this->Bomb = *Bomb;
	this->Bomb.setScale(10, 10);
	this->Bomb.setOrigin(sf::Vector2f(this->Bomb.getTexture()->getSize().x / 10, this->Bomb.getTexture()->getSize().y / 10));
	this->BombAnimate = new Animation(Bomb->getTexture(), sf::Vector2u(5, 5), 0.04f);

	bufWear.loadFromFile("Sound/wear.ogg");
	bufitem.loadFromFile("Sound/item.ogg");
	SoundWear.setBuffer(bufWear);
	SoundItem.setBuffer(bufitem);
}

void Item::update(sf::Sprite *ground, sf::View *view)
{
	BombAnimate->update(4, clockBomb.restart().asSeconds());
	for (int i = 0; i < itemDrop.size(); i++)
	{
		itemDrop[i].sprite.setPosition(sf::Vector2f(itemDrop[i].PointStr.getPosition().x, itemDrop[i].PointStr.getPosition().y - itemDrop[i].sprite.getTexture()->getSize().y*1/6));
		if (!Collision::CollisionCheck(&itemDrop[i].PointStr, ground, Collision::Down))
		{
			itemDrop[i].PointStr.move(0,1);
		}
	}
	Table.setPosition(sf::Vector2f(view->getCenter().x+185, view->getCenter().y+95));
	ClothesTable.setPosition(sf::Vector2f(view->getCenter().x + 215, view->getCenter().y - 350));
	TalbeBotton.setPosition(sf::Vector2f(view->getCenter().x + 185, view->getCenter().y + 95));
	ClothesTableBotton.setPosition(sf::Vector2f(view->getCenter().x + 215, view->getCenter().y - 350));
	for (int i = 0; i < 6; i++)
	{
		int row;
		int column;
		if (i < 3)
		{
			row = 3;
			column = 2 * (i + 1) + 1;
		}
		else
		{
			row = 5;
			column = 2 * (i - 2) + 1;
		}
		if (itemTable[i].state == true)
		{
			itemTable[i].sprite.setPosition(sf::Vector2f(view->getCenter().x + 185 + (talbe.getSize().x / 10*0.7 *column), view->getCenter().y + 95 + (talbe.getSize().y / 8*0.7 * row)));
		}
		
	}
	for (int i = 0 ; i < 4 ; i++)
	{
		itemHatTable[i].sprite.setPosition(sf::Vector2f(view->getCenter().x + 215 + (clothesTable.getSize().x / 10 * 0.7 * 3), view->getCenter().y - 350 + (clothesTable.getSize().y / 6 * 0.7 * 3)));
	}
	for (int i = 0; i < 4; i++)
	{
		itemClothesTable[i].sprite.setPosition(sf::Vector2f(view->getCenter().x + 215 + (clothesTable.getSize().x / 10 * 0.7 * 5), view->getCenter().y - 350 + (clothesTable.getSize().y / 6 * 0.7 * 3)));
	}
	for (int i = 0; i < 5; i++)
	{
		itemBulletTable[i].sprite.setPosition(sf::Vector2f(view->getCenter().x + 215 + (clothesTable.getSize().x / 10 * 0.7 * 7), view->getCenter().y - 350 + (clothesTable.getSize().y / 6 * 0.7 * 3)));
	}
}

void Item::draw(sf::RenderWindow * window)
{
	if (delayBomb.getElapsedTime().asSeconds() < 0.18)
	{
		Bomb.setTextureRect(BombAnimate->mRect);
		window->draw(Bomb);
	}
	for (int i = 0 ; i < itemDrop.size() ; i++)
	{
		if (itemDrop[i].kind != 0)
		{
			itemDrop[i].sprite.setScale(0.5,0.5);
		}
		window->draw(itemDrop[i].sprite);
		if (itemDrop[i].kind != 0)
		{
			itemDrop[i].sprite.setScale(0.7, 0.7);
		}
	}
	window->draw(Table);
	window->draw(ClothesTable);
	for (int i = 0 ; i < 6 ; i++)
	{
		if (itemTable[i].state == true)
		{
			window->draw(itemTable[i].sprite);
		}
	}
	window->draw(itemHatTable[itemHatType].sprite);
	window->draw(itemClothesTable[itemClothesType].sprite);
	window->draw(itemBulletTable[itemBulletType].sprite);
	window->draw(TalbeBotton);
	window->draw(ClothesTableBotton);
}

void Item::add(int ran,sf::Vector2f position)
{
	if (ran % 100 < 70)
	{
		if ((ran * 3 / 11) % 100 < 60)
		{
			if (ran*4/7%100 < 25)
			{
				itemDropType i = { this->SpriteCommon[0],this->Point , 0 , 0};
				i.PointStr.setPosition(position);
				itemDrop.push_back(i);
			}
			else
			{
				itemDropType i = { this->SpriteCommon[1],this->Point , 0 ,1 };
				i.PointStr.setPosition(position);
				itemDrop.push_back(i);
			}
		}
		else
		{
			if (ran * 9/5 % 100 < 30)
			{
				int Type = (ran % 2)+1;
				itemDropType i = { this->SpriteHat[Type],this->Point , 1 ,Type};
				i.PointStr.setPosition(position);
				itemDrop.push_back(i);
			}
			else if (ran * 9 / 5 % 100 <60)
			{
				int Type = (ran % 2)+1;
				itemDropType i = { this->SpriteClothes[Type],this->Point , 2 ,Type};
				i.PointStr.setPosition(position);
				itemDrop.push_back(i);
			}
			else
			{
				int Type = (ran % 4)+1;
				itemDropType i = { this->SpriteBullet[Type],this->Point , 3 ,Type};
				i.PointStr.setPosition(position);
				itemDrop.push_back(i);
			}
		}
	}

}

void Item::use(Player *player, Enemy::Dargon *enemy ,sf::View *view, int ran ,bool *checkRight, int *score)
{
	bool state[12];
	state[1] =( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < -85));
	state[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > 20);
	state[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > 20);
	state[4] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) or (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < -85);
	state[5] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) or sf::Joystick::isButtonPressed(0, 4);
	state[6] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6) or sf::Joystick::isButtonPressed(0, 5);
	state[7] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I) or sf::Joystick::isButtonPressed(0,2);
	state[8] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O) or sf::Joystick::isButtonPressed(0, 3);
	state[9] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) or sf::Joystick::isButtonPressed(0, 1);
	state[10] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) or sf::Joystick::isButtonPressed(0, 9);
	state[11] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete) or sf::Joystick::isButtonPressed(0, 6);

	for (int i = 1; i < 7; i++)
	{
		if (state[i] && !lastState[i] && itemTable[i-1].state)
		{
			if (itemTable[i - 1].Type == 1)
			{
				player->heal(500);
			}
			if (itemTable[i - 1].Type == 2)
			{
				player->powerUp(20);
			}
			itemTable[i-1].state = false;
			SoundItem.play();
		}
	}
	for (int i = 7 ; i <= 9 ; i++)
	{
		if (state[i] && !lastState[i])
		{
			SoundWear.play();
			if (i == 7 )
			{
				if (itemHatTable[itemHatType + 1].state) {
					if (itemHatType == 2)
					{
						itemHatType = 0;
					}
					else {
						itemHatType++;
					}
				}
				else {
					itemHatType = 0;
				}
			}
			else if (i == 8 )
			{
				if (itemClothesTable[itemClothesType + 1].state) {
					if (itemClothesType == 3)
					{
						itemClothesType = 0;
					}
					else {
						itemClothesType++;
					}
				}
				else {
					itemClothesType = 0;
				}
			}
			else if (i == 9)
			{
	
				if (itemBulletTable[itemBulletType + 1].state) {
					if (itemBulletType == 4)
					{
						itemBulletType = 0;
					}
					else {
						itemBulletType++;
					}
				}
				else {
					itemBulletType = 0;
				}
			}
			player->wear(itemHatTable[itemHatType].Type, itemClothesTable[itemClothesType].Type, itemBulletTable[itemBulletType].Type,*checkRight);
		}
	}
	if (state[10] && !lastState[10] and player->power == 100)
	{
		Bomb.setPosition(view->getCenter());
		BombAnimate->currentImage.x = 0;
		delayBomb.restart().asSeconds();

		player->power = 0;
		int n1 = 1, n2 = 551;
		for (int i = 0; i < enemy->enemy.size(); i++)
		{
			enemy->enemy[i].attacked(player->attack);
			enemy->textPrint(player->attack, { enemy->enemy[i].sprite.getPosition().x , enemy->enemy[i].sprite.getPosition().y });
			if (enemy->enemy[i].enemyHP <= 0)
			{
				add(ran*n1*n2, enemy->enemy[i].sprite.getPosition());
				enemy->enemy.erase(enemy->enemy.begin() + i);
			}
			n1 *= 3;
			n2 -= 5;
		}
	}
	if ((state[11] && !lastState[11]))
	{
		Bomb.setPosition(view->getCenter());
		BombAnimate->currentImage.x = 0;
		delayBomb.restart().asSeconds();
		int n1 = 1, n2 = 550;
		for (int i = 0; i < enemy->enemy.size(); i++)
		{
			enemy->enemy[i].attacked(9999);
			enemy->textPrint(9999, { enemy->enemy[i].sprite.getPosition().x , enemy->enemy[i].sprite.getPosition().y });
			if (enemy->enemy[i].enemyHP <= 0)
			{
				add(ran*n1*n2, enemy->enemy[i].sprite.getPosition());
				enemy->enemy.erase(enemy->enemy.begin() + i);
				*score += 1;
				i--;
			}
			n1 *= 3;
			n2 -= 5;
		}
	}

	for (int i = 1 ; i < 12 ; i++)
	{
		lastState[i] = state[i];
	}
}

void Item::keep(Player *player)
{
	for (int i = 0 ; i < itemDrop.size() ; i++)
	{
		if (Collision::PixelPerfectTest(&player->sprite, &itemDrop[i].sprite))
		{
			if (itemDrop[i].kind == 0)
			{
				for (int n = 0; n < 6; n++)
				{
					if (itemTable[n].state == false)
					{
						itemTable[n].sprite = itemDrop[i].sprite;
						itemTable[n].Type = itemDrop[i].type + 1;
						itemTable[n].state = true;
						itemDrop.erase(itemDrop.begin() + i);
						break;
					}
				}
			}
			else if (itemDrop[i].kind == 1)
			{
				for (int n = 0 ; n < 4 ; n++)
				{
					if (!itemHatTable[n].state )
					{
						bool check = true;
						for (int j = 0 ; j < 3 ; j++)
						{
							if (itemDrop[i].type == countHat[j])
							{
								check = false;
							}
						}
						if (check)
						{
							itemHatTable[n].sprite = itemDrop[i].sprite;
							itemHatTable[n].Type = itemDrop[i].type;
							itemHatTable[n].state = true;
							countHat[n] = itemDrop[i].type;
							break;
						}
					}
				}
				itemDrop.erase(itemDrop.begin() + i);
			}
			else if (itemDrop[i].kind == 2)
			{
				for (int n = 0; n < 4; n++)
				{
					if (!itemClothesTable[n].state)
					{
						bool check = true;
						for (int j = 0; j < 4; j++)
						{
							if (itemDrop[i].type == countClothes[j])
							{
								check = false;
							}
						}
						if (check)
						{
							itemClothesTable[n].sprite = itemDrop[i].sprite;
							itemClothesTable[n].Type = itemDrop[i].type;
							itemClothesTable[n].state = true;
							countClothes[n] = itemDrop[i].type;
							break;
						}
					}
				}
				itemDrop.erase(itemDrop.begin() + i);
			}
			else if (itemDrop[i].kind == 3)
			{
				for (int n = 0; n < 5; n++)
				{
					if (!itemBulletTable[n].state)
					{
						bool check = true;
						for (int j = 0; j < 5; j++)
						{
							if (itemDrop[i].type == countBullet[j])
							{
								check = false;
							}
						}
						if (check)
						{
							itemBulletTable[n].sprite = itemDrop[i].sprite;
							itemBulletTable[n].Type = itemDrop[i].type;
							itemBulletTable[n].state = true;
							countBullet[n] = itemDrop[i].type;
							break;
						}
					}
				}
				itemDrop.erase(itemDrop.begin() + i);
			}
		}
	}
}

void Item::clear()
{

	itemHatType = 0, itemClothesType = 0, itemBulletType = 0;
	for (int i = 0 ; i < 5 ; i++)
	{
		countBullet[i] = -10;
		itemBulletTable[i].state = false;
	}
	for (int i = 0; i < 4; i++)
	{
		countClothes[i] = -10;
		itemClothesTable[i].state = false;
	}
	for (int i = 0; i < 3; i++)
	{
		countHat[i] = -10;
		itemHatTable[i].state = false;
	}
	for (int i = 0; i < 6; i++)
	{
		itemTable[i].state = false;
	}

	itemDrop.clear();

	itemBulletTable[0].sprite = SpriteBullet[0];
	itemBulletTable[0].Type = 0;
	itemBulletTable[0].state = true;
	countBullet[0] = 0;

	itemHatTable[0].sprite = SpriteHat[0];
	itemHatTable[0].state = true;
	itemHatTable[0].Type = 0;
	countHat[0] = 0;

	itemClothesTable[0].sprite = SpriteClothes[0];
	itemClothesTable[0].state = true;
	itemClothesTable[0].Type = 0;
	countClothes[0] = 0;
}

Item::~Item()
{
}

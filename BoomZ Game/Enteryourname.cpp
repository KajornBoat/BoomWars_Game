#include "Enteryourname.h"


Enteryourname::Enteryourname(sf::RenderWindow *window)
{
	bgTexture.loadFromFile("Picture/menu/backName.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(sf::Vector2f(window->getSize().x / (float)this->bgTexture.getSize().x, window->getSize().y / (float)this->bgTexture.getSize().y));
	name_font.loadFromFile("Fonts/Superspace Bold ver 1.00.ttf");
	name.setFont(name_font);
	name.setPosition(sf::Vector2f(window->getSize().x / 2, 500));
	this->windows = window;
}
void Enteryourname::runEnter(bool chEnter)
{
	while (chEnter) 
	{
		while (windows->pollEvent(event)) {
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == '\b' && yourname.getSize() > 0) {
					yourname.erase(yourname.getSize() - 1, 1);
					name.setFont(name_font);
					name.setString(yourname);
				}
				else if (yourname.getSize() < 15 && event.text.unicode < 127 && event.text.unicode > 32) {
					std::string name_input;
					yourname += static_cast<char>(event.text.unicode);
					name_input += static_cast<char>(event.text.unicode);
	
					if (event.text.unicode < 128) {
						name.setFont(name_font);
						name.setString(yourname);
					}
				}
				name.setFillColor(sf::Color::White);
				name.setCharacterSize(60);
				name.setPosition((sf::Vector2f(windows->getSize().x / 2.0, 670)));
				name.setOrigin(sf::Vector2f(name.getGlobalBounds().width / 2, 0));
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Return && yourname.getSize() > 0) {
					name.setString(yourname);
					chEnter = false;
				}
			}
			if (this->event.type == sf::Event::Closed)
			{
				chEnter = false;
				windows->close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				chEnter = false;
				yourname.clear();
				name.setString(yourname);
			}
		}

		windows->clear();

		windows->draw(bgSprite);
		windows->draw(name);

		windows->display();


	}
}


Enteryourname::~Enteryourname()
{
}



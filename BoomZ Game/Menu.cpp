#include "Menu.h"



Menu::Menu(sf::RenderWindow *window,int *score)
{
	this->window = window;
	this->texture.loadFromFile("Picture/menu/back.png");
	this->playbotton.loadFromFile("Picture/menu/play.png");
	this->scorebotton.loadFromFile("Picture/menu/score.png");
	this->exitbotton.loadFromFile("Picture/menu/exit.png");
	this->sprite.setTexture(this->texture);
	this->playBotton.setTexture(this->playbotton);
	this->scoreBotton.setTexture(this->scorebotton);
	this->exitBotton.setTexture(this->exitbotton);
	this->sprite.setScale(sf::Vector2f(window->getSize().x / (float)this->texture.getSize().x, window->getSize().y / (float)this->texture.getSize().y));
	this->playBotton.setScale(0.8,0.8);
	this->playBotton.setOrigin(sf::Vector2f(this->playbotton.getSize().x/2, 0));
	this->scoreBotton.setOrigin(sf::Vector2f(this->scorebotton.getSize().x / 2, 0));
	this->exitBotton.setOrigin(sf::Vector2f(this->exitbotton.getSize().x / 2, 0));
	this->playBotton.setPosition(sf::Vector2f(this->window->getSize().x/2,400));
	this->scoreBotton.setPosition(sf::Vector2f(this->window->getSize().x / 2,550));
	this->exitBotton.setPosition(sf::Vector2f(this->window->getSize().x / 2, 650));
	this->scoreBotton.setScale(0.8,0.8);
	this->exitBotton.setScale(0.8,0.8);
	enterName = new Enteryourname(window);
	this->Score = score;

	text.setCharacterSize(70);
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(window->getSize().x/2, window->getSize().y / 2));
	text.setFont(enterName->name_font);

	textName.setString(strname);
	textName.setCharacterSize(35);
	textName.setFillColor(sf::Color::Red);
	textName.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2+330));
	textName.setFont(enterName->name_font);
	textName.setOrigin(textName.getGlobalBounds().width / 2, textName.getGlobalBounds().height / 2);
	textName.setOutlineColor(sf::Color::White);
	textName.setOutlineThickness(2);

	textBord.loadFromFile("Picture/common/scoreBord.png");
	spriteBord.setTexture(textBord);
	spriteBord.setOrigin(sf::Vector2f(textBord.getSize().x/2, textBord.getSize().y / 2));
	spriteBord.setPosition(sf::Vector2f(window->getSize().x/2, window->getSize().y / 2));
	soundMenuLoad.loadFromFile("Sound/menu.ogg");
	soundMenu.setBuffer(soundMenuLoad);
}

void Menu::run()
{
	soundMenu.play();
	soundMenu.setLoop(10);
	bool laststate = true,lastover = false;

	while (menucheck)
	{
		
		while (Overcheck)
		{

			bool state = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) ;
			while (this->window->pollEvent(this->event))
			{
				if (this->event.type == sf::Event::Closed)
				{
					this->Overcheck = false;
					menucheck = false;
					window->close();
				}
			}
			if (state && !lastover)
			{
				this->Overcheck = false;
				updateHighScore(enterName->yourname, *Score+Bonus);
				enterName->yourname.clear();
				enterName->name.setString(enterName->yourname);
				*Score = 0;
				Bonus = 0;
			}

			lastover = state;

			text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);

			window->setView(window->getDefaultView());
			window->clear();

			window->draw(this->sprite);
			window->draw(text);

			window->display();
		}
		bool state = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);

		window->clear();

		window->draw(this->sprite);
		window->draw(this->scoreBotton);
		window->draw(this->exitBotton);
		window->draw(this->playBotton);
		window->draw(textName);

		window->display();

		this->playBotton.setColor(sf::Color(this->playBotton.getColor().r, this->playBotton.getColor().g, this->playBotton.getColor().b,170));
		this->scoreBotton.setColor(sf::Color(this->scoreBotton.getColor().r, this->scoreBotton.getColor().g, this->scoreBotton.getColor().b, 170));
		this->exitBotton.setColor(sf::Color(this->exitBotton.getColor().r, this->exitBotton.getColor().g, this->exitBotton.getColor().b, 170));
		
		this->Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
		this->Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

		if (Up&&!lastUp)
		{
			this->bottonState--;
			if (this->bottonState == -1)
			{
				this->bottonState = 2;
			}
		}
		if (Down&&!lastDown)
		{
			this->bottonState++;
			if (this->bottonState == 3)
			{
				this->bottonState = 0;
			}
		}
		lastDown = Down, lastUp = Up;

		if (this->bottonState == munuState::play)
		{
			this->playBotton.setColor(sf::Color(this->playBotton.getColor().r, this->playBotton.getColor().g, this->playBotton.getColor().b, 255));
			if (state && !laststate)
			{
				enterName->runEnter(enterName->checkEnter);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					this->menucheck = true;
				}
				else {
					this->menucheck = false;
				}
			}
			laststate = state;
		}
		else if (this->bottonState == munuState::score)
		{
			this->scoreBotton.setColor(sf::Color(this->scoreBotton.getColor().r, this->scoreBotton.getColor().g, this->scoreBotton.getColor().b, 255));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				checkHighScore = true;
				showHighscore();
			}
		}
		else if (this->bottonState == munuState::exit)
		{
			this->exitBotton.setColor(sf::Color(this->exitBotton.getColor().r, this->exitBotton.getColor().g, this->exitBotton.getColor().b, 255));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				this->menucheck = false;
				this->window->close();
			}
		}

		while (this->window->pollEvent(this->event))
		{
			if (this->event.type == sf::Event::Closed)
			{
				this->menucheck = false;
				window->close();
			}
		}
	}
}

void Menu::Text()
{
	str = "Your Score : ";
	str += std::to_string(*Score);
	str += "+";
	str += std::to_string(Bonus);
	str += " = ";
	str += std::to_string(*Score + Bonus);
	text.setString(str);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(10);
}

void Menu::updateHighScore(std::string name, int score)
{
	std::fstream myFile;
	std::string word;

	myFile.open("highScore.dat");
	if (myFile.is_open())
	{
		std::cout << "open control.dat success\n";
	}
	else
	{
		std::cout << "open control.dat failed\n";
	}

	std::vector<std::pair<std::string, int> > vtHighScore;
	std::string tmpName, tmpFloat;
	while (std::getline(myFile, word))
	{
		if (word.find("name") != std::string::npos)
		{
			tmpName = "";
			tmpFloat = "";
			for (int i = 0; i < 20; i++)
			{
				tmpName += word[word.find("name:") + std::string("name:").length() + i];
			}
			for (int i = word.find("score:") + std::string("score:").length(); i < word.length(); i++)
			{
				tmpFloat += word[i];
			}
			int result;
			if (tmpFloat != "                    ")
			{
				result = std::stoi(tmpFloat, NULL);
			}
			else
			{
				result = -1.0;
			}
			vtHighScore.push_back(std::make_pair(tmpName, result));
		}

	}
	myFile.close();
	vtHighScore.push_back(std::make_pair(name, score));
	for (int i = 0; i < vtHighScore.size(); i++)
	{
		for (int j = i + 1; j < vtHighScore.size(); j++)
		{
			if (vtHighScore[j].second > vtHighScore[i].second)
			{
				std::swap(vtHighScore[i], vtHighScore[j]);
			}
		}
	}
	for (int i = 0; i < vtHighScore.size(); i++)
	{
		std::cout << vtHighScore[i].first << " , " << vtHighScore[i].second << "\n";
	}
	std::ofstream myfile2;
	myfile2.open("highScore.dat", std::ofstream::out | std::ofstream::trunc);
	myfile2 << "<highScore>\n";
	myfile2 << "01name:" << std::left << std::setw(20) << vtHighScore[0].first << "score:" << std::left << std::setw(20) << vtHighScore[0].second << "\n";
	myfile2 << "02name:" << std::left << std::setw(20) << vtHighScore[1].first << "score:" << std::left << std::setw(20) << vtHighScore[1].second << "\n";
	myfile2 << "03name:" << std::left << std::setw(20) << vtHighScore[2].first << "score:" << std::left << std::setw(20) << vtHighScore[2].second << "\n";
	myfile2 << "04name:" << std::left << std::setw(20) << vtHighScore[3].first << "score:" << std::left << std::setw(20) << vtHighScore[3].second << "\n";
	myfile2 << "05name:" << std::left << std::setw(20) << vtHighScore[4].first << "score:" << std::left << std::setw(20) << vtHighScore[4].second << "\n";
	myfile2 << "</highScore>\n";
	myfile2.close();

}

std::vector<std::pair<std::string, int>> Menu::HighScore()
{
	std::fstream myFile;
	std::string word;
	myFile.open("highScore.dat");
	if (myFile.is_open())
	{
		std::cout << "open control.dat success\n";
	}
	else
	{
		std::cout << "open control.dat failed\n";
	}
	std::vector < std::pair < std::string, int> > scoreList;
	std::string tmpName, tmpScore;
	while (std::getline(myFile, word))
	{
		if (word.find("name:") != std::string::npos)
		{
			tmpName = "";
			for (int i = word.find("name:") + std::string("name:").length(); i < word.find("score:"); i++)
			{
				tmpName += word[i];
			}
			tmpScore = "";
			for (int i = word.find("score:") + std::string("score:").length(); i < word.length(); i++)
			{
				tmpScore += word[i];
			}
			if (tmpScore != "                    ")
			{
				scoreList.push_back(std::make_pair(tmpName, std::stoi(tmpScore, NULL)));
			}
			else
			{
				scoreList.push_back(std::make_pair(tmpName, -1));
			}
		}
	}
	myFile.close();

	return std::vector<std::pair<std::string, int>> (scoreList);
}

void Menu::showHighscore()
{
	std::vector<std::pair<std::string, int>> temp = HighScore();
	for (int i = 0; i < 5; i++)
	{
		if (temp[i].second > -1)
		{
			textScoreName[i].setString(temp[i].first);
			textScoreName[i].setFont(enterName->name_font);
			textScoreName[i].setCharacterSize(50);
			textScoreName[i].setFillColor(sf::Color::Black);
			textScoreName[i].setOrigin(sf::Vector2f(textScoreName[i].getGlobalBounds().width / 2,0));
			textScoreName[i].setPosition(sf::Vector2f(520, 400 + (i * 60)));
			
			textScore[i].setString(std::to_string(temp[i].second));
			textScore[i].setFont(enterName->name_font);
			textScore[i].setCharacterSize(50);
			textScore[i].setFillColor(sf::Color::Black);
			textScore[i].setOrigin(sf::Vector2f(textScore[i].getGlobalBounds().width / 2, 0));
			textScore[i].setPosition(sf::Vector2f(1000 , 400 + (i * 60)));
		
		}
		
	}
	while (checkHighScore)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			checkHighScore = false;
		}
		while (this->window->pollEvent(this->event))
		{
			if (this->event.type == sf::Event::Closed)
			{
				checkHighScore = false;
				menucheck = false;
				window->close();
			}
		}

		window->clear();

		window->draw(this->sprite);
		window->draw(spriteBord);

		for (int i = 0; i < 5; i++)
		{
			if (temp[i].second > -1)
			{
				window->draw(textScoreName[i]);
				window->draw(textScore[i]);
			}

		}
		

		window->display();
	}
}



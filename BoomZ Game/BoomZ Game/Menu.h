#pragma once
#include <SFML/Graphics.hpp>
#include"Enteryourname.h"
#include <iostream>
#include<fstream>
#include <iomanip>
#include <string>
#include<SFML/Audio.hpp>

class Menu
{

public:
	Menu(sf::RenderWindow *window,int *score);
	void run();
	void Text();
	void updateHighScore(std::string name, int score);
	std::vector < std::pair < std::string, int> > HighScore();
	void showHighscore();
	Enteryourname *enterName;
	bool menucheck = true;
	bool Overcheck = false;
	int *Score;
	int Bonus = 0;
private:
	enum  munuState
	{
		play, score, exit
	};

	sf::RenderWindow *window;
	sf::Event event;
	sf::Texture texture,playbotton,scorebotton,exitbotton;
	sf::Sprite sprite,playBotton,scoreBotton,exitBotton;
	munuState pageState;
	int bottonState = 0;
	bool lastUp = false , lastDown = false, Up, Down, checkHighScore = true;

	sf::Text text,textScoreName[5],textScore[5];
	std::string str;

	sf::Text textName;
	std::string strname = "Kajorn Boonjaroen 61010107";

	sf::Texture textBord;
	sf::Sprite spriteBord;

	sf::SoundBuffer soundMenuLoad;
	sf::Sound soundMenu;


};


#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Animation.h"
class Sprite
{
public:
	class UI
	{
	public:

		UI();
		void draw(sf::RenderWindow *window);
		void update(sf::View &view, int Angle);

		sf::Sprite Scale, RedNeedle, HPbar;
		sf::RectangleShape RedBar , YellowBar , HP ,Power ;
		int RedBarSize, YellowBarSize, hpSize , PowerSize;
		sf::Text TextAngle;
		sf::Font fonts;

	private:

		sf::Texture scale, redNeedle, redBar, yellowBar, hpbar, hp,power;

	};

	class Common
	{
	public:
		Common();
		void draw(sf::RenderWindow *window);
		sf::Sprite Bomb, Degree, Point;
		Animation *BombAnimate;
		sf::Texture bomb, degree, point;
		sf::Sound playSound,SoundStart, SoundDead, SoundWin,SoundWalk,SoundChart,SoundShoot;
	private:
		sf::SoundBuffer soundbuf,bufstart,bufdead,bufwin,bufwalk,bufChart,bufShoot;

	};

public:
	Sprite();
private:

};


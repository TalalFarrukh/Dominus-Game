#ifndef PLAYERS_H_
#define PLAYERS_H_
#include "Spells.h"
#include "Characters.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <string>
using namespace std;
using namespace sf;


class Player
{
private:
	Character Infernus, Fridgus, Empyreus, Messor;
	string HH, SS;
public:
	int check;
	static int counter;
	Character Select;
	Player(int c) : Infernus(100, 80, "Infernus"), Fridgus(100, 70, "Fridgus"), Empyreus(150, 60, "Empyreus"), Messor(180, 60, "Messor") { check = c; }
	string name;
	Text H, S, US;
	Font font;

	int select(int mp_x, int mp_y) {
		int i = 0;
		if (Mouse::isButtonPressed(Mouse::Button::Left) && mp_x >= 0 && mp_x < 300 && mp_y >= 100 && mp_y <= 270 && counter != 1) {
			i = 1; counter = 1;
			Select = Messor, Select.select(i, check);
			return i;
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Left) && mp_x >= 300 && mp_x < 600 && mp_y >= 100 && mp_y <= 270 && counter != 2) {
			i = 2; counter = 2;
			Select = Empyreus, Select.select(i, check);
			return i;
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Left) && mp_x >= 600 && mp_x < 900 && mp_y >= 100 && mp_y <= 270 && counter != 3) {
			i = 3; counter = 3;
			Select = Infernus, Select.select(i, check);
			return i;
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Left) && mp_x >= 900 && mp_x <= 1200 && mp_y >= 100 && mp_y <= 270 && counter != 4) {
			i = 4; counter = 4;
			Select = Fridgus, Select.select(i, check);
			return i;
		}
		else
			return 0;
	}

	void textdisplay() {
		font.loadFromFile("Textures/Rocko.ttf");
		US.setFont(font); US.setFillColor(Color::White); US.setCharacterSize(26); US.setString(name);
		H.setFont(font); H.setFillColor(Color::Black); H.setCharacterSize(22); 
		S.setFont(font); S.setFillColor(Color::Black); S.setCharacterSize(22); 

		HH = "Health: " + to_string(Select.health) + "/" + to_string(Select.healtho); SS = "Stamina: " + to_string(Select.stamina) + "/" + to_string(Select.staminao);
		H.setString(HH); S.setString(SS);

		if (check == 1) {
			US.setPosition(20.f, 50.f); H.setPosition(210.f, 60.f); S.setPosition(210.f, 110.f);
		}
		else if (check == 2) {
			US.setPosition(1020.f, 50.f); H.setPosition(810.f, 60.f); S.setPosition(810.f, 110.f);
		}
	}

	void setsetTextures(int r) {
		Select.setTextures(r,check);
	}
};

int Player::counter = 0;

#endif

#ifndef SPELLS_H_
#define SPELLS_H_
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

class Spells
{
private:
	int damage, cost;
	Texture O; Font font;
public:
	string name;
	Sprite Option; Text Optiondesc;

	Spells() {}
	Spells(int d, int c, string n) {
		damage = d; cost = c; name = n;
	}

	void optionset(float pos_x, float pos_y, int n, float pos_x2, float pos_y2) {
		font.loadFromFile("Textures/Rocko.ttf");
		if (n == 1)
			O.loadFromFile("Textures/ChoiceMessor.png");
		else if (n == 2)
			O.loadFromFile("Textures/ChoiceEmpyreus.png");
		else if (n == 3)
			O.loadFromFile("Textures/ChoiceInfernus.png");
		else if (n == 4)
			O.loadFromFile("Textures/ChoiceFridgus.png");

		Option.setTexture(O); Option.setOrigin(150.f, 35.f); Option.setPosition(pos_x, pos_y); Option.setScale(1.15f, 1.f);
		Optiondesc.setFont(font); Optiondesc.setCharacterSize(20); Optiondesc.setFillColor(Color::Black); 
		Optiondesc.setPosition(pos_x2, pos_y2); Optiondesc.setString(name);
	}

	int atk() {
		return damage;
	}
	int stm() {
		return cost;
	}
};

#endif

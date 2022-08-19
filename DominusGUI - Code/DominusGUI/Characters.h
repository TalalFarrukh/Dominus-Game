#ifndef CHARACTERS_H_
#define CHARACTERS_H_
#include "Spells.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

class Character
{
public:
	Spells FB, LB, IB, DB, Heal, FBB, IBB, LBB, DBB, Skip;
	int health, healtho, stamina, staminao;
	int cc;
	string name, atkm;
	Texture texture, textureH, textureS;

	Spells ppp[4];
	Sprite Pic, HBar, SBar; 
	Character() {}
	Character(int h, int s, string n) : FB(10, 8, "Fire Bolt (Atk=10, Cost=8)"), IB(8, 6, "Ice Blow (Atk=8, Cost=6)"),
		LB(12, 12, "Lightning Bolt (Atk=12, Cost=12)"), DB(15, 12, "Death Blow (Atk=15, Cost=12)"), Heal(-20, 10, "Heal (Heal=20, Cost=10)"),
		FBB(28, 16, "Fire Blast (Atk=28, Cost=16)"), IBB(24, 14, "Ice Blast (Atk=24, Cost=14)"), LBB(34, 20, "Lightning Blast (Atk=34, Cost=20)"), DBB(40, 25, "Death Blast (Atk=40, Cost=25)"), 
		Skip(0, 0, "Skip")
	{
		healtho = h; health = h; stamina = s; staminao = s; name = n; cc = 10;
		Pic.setOrigin(100.f, 100.f);
	}

	string checkname() {
		return name;
	}

	void setTextures(int r, int c) {
		if (r == 1 && c == 1)
			texture.loadFromFile("Textures/DMessor.png");
		else if (r == 2  && c == 1)
			texture.loadFromFile("Textures/DEmpyreus.png");
		else if (r == 3 && c == 1)
			texture.loadFromFile("Textures/DInfernus.png");
		else if (r == 4 && c == 1)
			texture.loadFromFile("Textures/DFridgus.png");
		else if (r == 1 && c == 2)
			texture.loadFromFile("Textures/DMessorR.png");
		else if (r == 2 && c == 2)
			texture.loadFromFile("Textures/DEmpyreusR.png");
		else if (r == 3 && c == 2)
			texture.loadFromFile("Textures/DInfernusR.png");
		else if (r == 4 && c == 2)
			texture.loadFromFile("Textures/DFridgusR.png");

		textureH.loadFromFile("Textures/HBar.png"), textureS.loadFromFile("Textures/SBar.png");
		HBar.setTexture(textureH); SBar.setTexture(textureS); 
		
		Pic.setTexture(texture); Pic.setOrigin(100.f, 100.f);

		if (c == 1) {
			Pic.setPosition(150.f, 250.f); HBar.setPosition(200.f, 50.f); SBar.setPosition(200.f, 100.f);
		}
		else if (c == 2) {
			Pic.setPosition(1050.f, 250.f); HBar.setPosition(800.f, 50.f); SBar.setPosition(800.f, 100.f);
		}
		
	}

	void select(int n, int c) {
		if (n == 1)
			ppp[0] = DB, ppp[1] = DBB, ppp[2] = Heal, ppp[3] = Skip;
		else if (n == 2)
			ppp[0] = LB, ppp[1] = LBB, ppp[2] = Heal, ppp[3] = Skip;
		else if (n == 3)
			ppp[0] = FB, ppp[1] = FBB, ppp[2] = Heal, ppp[3] = Skip;
		else if (n == 4)
			ppp[0] = IB, ppp[1] = IBB, ppp[2] = Heal, ppp[3] = Skip;
		
		if (c == 1) {
			ppp[0].optionset(175.f, 350.f, n, 15.f, 335.f); ppp[1].optionset(175.f, 430.f, n, 15.f, 415.f); 
			ppp[2].optionset(175.f, 510.f, n, 15.f, 495.f); ppp[3].optionset(175.f, 590.f, n, 15.f,575.f);
		}
		else if (c == 2) {
			ppp[0].optionset(1025.f, 350.f, n, 865.f, 335.f); ppp[1].optionset(1025.f, 430.f, n, 865.f, 415.f); 
			ppp[2].optionset(1025.f, 510.f, n, 865.f, 495.f); ppp[3].optionset(1025.f, 590.f, n, 865.f, 575.f);
		}
	}

	Character action(Character C, int c, int x, int y) {
		int s1, s2;
		Character C3;
		C3 = C;

		srand(time(0));
		if (name == "Infernus") {
			s1 = rand() % 66; s2 = rand() % 15;
		}
		else if (name == "Fridgus") {
			s1 = rand() % 66; s2 = rand() % 15;
		}
		else if (name == "Empyreus") {
			s1 = rand() % 51; s2 = rand() % 13;
		}
		else if (name == "Messor") {
			s1 = rand() % 48; s2 = rand() % 12;
		}

		if (c == 1 && x >= 2.5 && x <= 347.5) {
			if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 315 && y <= 385 && stamina >= ppp[0].stm()) {
				if (s1 == 22 || s1 == 34) {
					atkm = "Attack failed"; stamina = stamina - 3;
				}
				else {
					C3.health = C.health - ppp[0].atk(); stamina = stamina - ppp[0].stm(); stamina = stamina + 3;
					atkm = name + " used " + ppp[0].name + " \non " + C3.name + "\nAttack was successful";
				}
				cc++;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 395 && y <= 465 && stamina >= ppp[1].stm()) {
				if (s2 == 5 || s2 == 9 || s2 == 11) {
					atkm = "Attack failed"; stamina = stamina - 3;
				}
				else {
					C3.health = C.health - ppp[1].atk(); stamina = stamina - ppp[1].stm(); stamina = stamina + 3;
					atkm = name + " used " + ppp[1].name + " \non " + C3.name + "\nAttack was successful";
				}
				cc++;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 475 && y <= 545 && stamina >= ppp[2].stm()) {
				if (health <= (healtho - (healtho * 0.2))) {
					health = health - ppp[2].atk(); stamina = stamina - ppp[2].stm();
					atkm = "Healing complete"; stamina = stamina + 3;
				}
				else {
					atkm = "Health above 80%, cannot use Heal yet"; cc++;
				}
				cc++;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 555 && y <= 625) {
				atkm = "Your turn has been skipped"; cc++;
				if (stamina <= (staminao - 3))
					stamina = stamina + 3;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && (stamina < ppp[0].stm() || stamina < ppp[1].stm() || stamina < ppp[2].stm())) {
				atkm = "Not enough stamina to attack"; stamina = stamina + 3; cc++;
			}
		}

		else if (c == 2 && x >= 852.5 && x <= 1197.5) {
			if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 315 && y <= 385 && stamina >= ppp[0].stm()) {
				if (s1 == 22 || s1 == 34) {
					atkm = "Attack failed"; stamina = stamina - 3;
				}
				else {
					C3.health = C.health - ppp[0].atk(); stamina = stamina - ppp[0].stm(); stamina = stamina + 3;
					atkm = name + " used " + ppp[0].name + " \non " + C3.name + "\nAttack was successful";
				}
				cc++;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 395 && y <= 465 && stamina >= ppp[1].stm()) {
				if (s2 == 5 || s2 == 9 || s2 == 11) {
					atkm = "Attack failed"; stamina = stamina - 3;
				}
				else {
					C3.health = C.health - ppp[1].atk(); stamina = stamina - ppp[1].stm(); stamina = stamina + 3;
					atkm = name + " used " + ppp[1].name + " \non " + C3.name + "\nAttack was successful";
				}
				cc++;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 475 && y <= 545 && stamina >= ppp[2].stm()) {
				if (health <= (healtho - (healtho * 0.2))) {
					health = health - ppp[2].atk(); stamina = stamina - ppp[2].stm();
					atkm = "Healing complete"; stamina = stamina + 3;
				}
				else {
					atkm = "Health above 80%, cannot use Heal yet"; cc++;
				}
				cc++;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && y >= 555 && y <= 625) {
				atkm = "Your turn has been skipped"; cc++;
				if (stamina <= (staminao - 3))
					stamina = stamina + 3;
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Left) && (stamina < ppp[0].stm() || stamina < ppp[1].stm() || stamina < ppp[2].stm())) {
				atkm = "Not enough stamina to attack"; stamina = stamina + 3; cc++;
			}
		}
		return C3;
	}
};

#endif
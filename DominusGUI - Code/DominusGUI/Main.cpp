#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Spells.h"
#include "Characters.h"
#include "Players.h"
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow MW(VideoMode(1200, 650), "Dominus", Style::Close | Style::Titlebar);
    MW.setFramerateLimit(30);
    
    Music bgmusic; bgmusic.openFromFile("Textures/BGMusic.ogg"); bgmusic.setVolume(15);

    //Textures delcaring and loading
    Texture bg, ExitB, MsgB, WinB;
    bg.loadFromFile("Textures/Background.png"); ExitB.loadFromFile("Textures/ExitB.png");
    MsgB.loadFromFile("Textures/MsgB.png"); WinB.loadFromFile("Textures/WinB.png");

    //Sprite     
    Sprite background, Exit, MsgBox, InstBox, WinBox;
    background.setTexture(bg); Exit.setTexture(ExitB); MsgBox.setTexture(MsgB), InstBox.setTexture(MsgB); WinBox.setTexture(WinB);
    Exit.setOrigin(150.f, 50.f); MsgBox.setOrigin(250.f, 75.f); InstBox.setOrigin(250.f, 75.f); WinBox.setOrigin(250.f, 125.f);
    Exit.setPosition(600.f, 20.f); MsgBox.setPosition(600.f, 450.f); InstBox.setPosition(600.f, 325.f); WinBox.setPosition(600.f, 325.f);
    Exit.setScale(0.6f, 0.6f); InstBox.setScale(2.f, 2.5f); WinBox.setScale(1.f, 0.8f);

    //Text and Font
    Font ALBA; ALBA.loadFromFile("Textures/Rocko.ttf");
    Text Prompt, username, Instructions, atkmsg, winmsg;
    Prompt.setFont(ALBA); Prompt.setCharacterSize(22); Prompt.setPosition(370.f, 390.f); Prompt.setFillColor(Color::Black);
    username.setFont(ALBA); username.setCharacterSize(22); username.setPosition(500.f, 280.f); username.setFillColor(Color::Black);
    Instructions.setFont(ALBA); Instructions.setCharacterSize(26); Instructions.setFillColor(Color::Black); Instructions.setPosition(120.f, 190.f);
    atkmsg.setFont(ALBA); atkmsg.setCharacterSize(20); atkmsg.setPosition(370.f, 390.f); atkmsg.setFillColor(Color::Black);
    winmsg.setFont(ALBA); winmsg.setCharacterSize(32); winmsg.setPosition(410.f, 280.f); winmsg.setFillColor(Color::Black);

    //Pointer textures, sprites and text
    Texture* PlayB; PlayB = new Texture; PlayB->loadFromFile("Textures/PlayB.png");
    Sprite* Play; Play = new Sprite; Play->setTexture(*PlayB); Play->setOrigin(200.f, 100.f); Play->setPosition(600.f, 325.f);

    Texture* EnterF; EnterF = new Texture; 
    Sprite* EnterField; EnterField = new Sprite;  
    EnterField->setOrigin(140.f, 35.f); EnterField->setPosition(600.f, 300.f); EnterField->setScale(1.2f, 1.f);

    Texture* CharM; CharM = new Texture; Texture* CharE; CharE = new Texture; Texture* CharI; CharI = new Texture; Texture* CharF = new Texture;
    Sprite* Messor; Messor = new Sprite; Sprite* Empyreus; Empyreus = new Sprite; Sprite* Infernus; Infernus = new Sprite; Sprite* Fridgus; Fridgus = new Sprite;
    Messor->setOrigin(100.f, 100.f), Empyreus->setOrigin(100.f, 100.f), Infernus->setOrigin(100.f, 100.f), Fridgus->setOrigin(100.f, 100.f);
    Messor->setPosition(150.f, 200.f), Empyreus->setPosition(450.f, 200.f), Infernus->setPosition(750.f, 200.f), Fridgus->setPosition(1050.f, 200.f);

    Sprite* ChoiceM; ChoiceM = new Sprite; Sprite* ChoiceE; ChoiceE = new Sprite; Sprite* ChoiceI; ChoiceI = new Sprite; Sprite* ChoiceF; ChoiceF = new Sprite;
    Texture* ChoiceM1; ChoiceM1 = new Texture; Texture* ChoiceE1; ChoiceE1 = new Texture; Texture* ChoiceI1; ChoiceI1 = new Texture; Texture* ChoiceF1; ChoiceF1 = new Texture;
    Text* ChoiceM2; ChoiceM2 = new Text; Text* ChoiceE2; ChoiceE2 = new Text; Text* ChoiceI2; ChoiceI2 = new Text; Text* ChoiceF2; ChoiceF2 = new Text;

    ChoiceM2->setFont(ALBA), ChoiceE2->setFont(ALBA), ChoiceI2->setFont(ALBA), ChoiceF2->setFont(ALBA);
    ChoiceM2->setCharacterSize(20), ChoiceE2->setCharacterSize(20), ChoiceI2->setCharacterSize(20), ChoiceF2->setCharacterSize(20);
    ChoiceM2->setFillColor(Color::Black), ChoiceE2->setFillColor(Color::Black), ChoiceI2->setFillColor(Color::Black), ChoiceF2->setFillColor(Color::Black);
    ChoiceM2->setPosition(25.f, 285.f), ChoiceE2->setPosition(310.f, 285.f), ChoiceI2->setPosition(625.f, 285.f), ChoiceF2->setPosition(925.f, 285.f);

    ChoiceM->setPosition(0.f, 270.f), ChoiceE->setPosition(300.f, 270.f), ChoiceI->setPosition(600.f, 270.f), ChoiceF->setPosition(900.f, 270.f);


    int MW_x = MW.getSize().x;
    int MW_y = MW.getSize().y;
    int r1=0, r2=0;

    string A1;
    string P1, P2;


    bool m1 = true, m2 = true, m3 = false, m4 = false, m5 = false, m6 = false, m7 = false, m8 = false, m9 = false;
    bool Turn1 = true, Turn2 = false;

    MW.draw(background); MW.draw(*Play); MW.draw(Exit);
    MW.display();
    bgmusic.play();

    Player Player1(1), Player2(2), temp1(0), temp2(0);

    while (MW.isOpen())
    {
        MW.setFramerateLimit(30);
        int mp_x = Mouse::getPosition(MW).x;
        int mp_y = Mouse::getPosition(MW).y;

        Event event;
        while (MW.pollEvent(event))
        {
            if (event.type == Event::Closed)
                MW.close();
        }

        //Exit Button
        if (Mouse::isButtonPressed(Mouse::Button::Left) && mp_x >= 450 && mp_x <= 750 && mp_y >= 0 && mp_y <= 100 && m1 == true) {
            m1 = false;
            MW.close();
        }
        //Play Button
        if (Mouse::isButtonPressed(Mouse::Button::Left) && mp_x >= 400 && mp_x <= 800 && mp_y >= 325 && mp_y <= 525 && m2 == true) { 
            delete Play, PlayB;
            MW.clear();
            MW.draw(background); MW.draw(Exit); MW.draw(MsgBox);
            MW.display();
            m2 = false; m3 = true;
        }

        if (m3 == true) {
            MW.setFramerateLimit(7);
            EnterF->loadFromFile("Textures/EnterField.png"); EnterField->setTexture(*EnterF);
            Prompt.setString("Enter your username Player 1");
            if (event.type == Event::TextEntered) {
                if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
                    Player1.name.erase(Player1.name.size() - 1, 1);
                    username.setString(Player1.name);
                }
                else {
                    Player1.name += event.text.unicode;
                    username.setString(Player1.name);
                }                
            }

            MW.clear();
            MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(Prompt), MW.draw(*EnterField), MW.draw(username);
            MW.display();

            if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                m3 = false; m4 = true;
                MW.setFramerateLimit(30);
            }
        }
        
        if (m4 == true) {
            MW.setFramerateLimit(7);
            Prompt.setString("Enter your username Player 2");
            if (event.type == Event::TextEntered) {
                if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
                    Player2.name.erase(Player2.name.size() - 1, 1);
                    username.setString(Player2.name);
                }
                else {
                    Player2.name += event.text.unicode;
                    username.setString(Player2.name);
                }
            }

            MW.clear();
            MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(Prompt), MW.draw(*EnterField), MW.draw(username);
            MW.display();

            if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                m4 = false; m5 = true;
                MW.setFramerateLimit(30);
                delete EnterF, EnterField;
            }
        }
        
        if (m5 == true){
            Instructions.setString("Instructions: \n1. Both players get turns, Player 1 starts first \n2. Player chooses an attack to attack their opponent \n3. The next player gets their turn and does the same \n4. Each attack requires stamina, if it runs out, the player cannot attack \n5. The player's stamina increases by 3 at the end of their turn \n6. The game goes on until the health of one player hits zero \nGood luck to both the players and have fun!");
            
            MW.clear();
            MW.draw(background), MW.draw(Exit), MW.draw(InstBox), MW.draw(Instructions);
            MW.display();
            
            Sleep(8000);
            m5 = false; m6 = true;
        }

        if (m6 == true) {
            MW.setFramerateLimit(7);
            CharM->loadFromFile("Textures/DMessor.png"), CharE->loadFromFile("Textures/DEmpyreus.png"), CharI->loadFromFile("Textures/DInfernus.png"), CharF->loadFromFile("Textures/DFridgus.png");
            Messor->setTexture(*CharM), Empyreus->setTexture(*CharE), Infernus->setTexture(*CharI), Fridgus->setTexture(*CharF);
            ChoiceM1->loadFromFile("Textures/ChoiceMessor.png"), ChoiceE1->loadFromFile("Textures/ChoiceEmpyreus.png"), ChoiceI1->loadFromFile("Textures/ChoiceInfernus.png"), ChoiceF1->loadFromFile("Textures/ChoiceFridgus.png");
            ChoiceM->setTexture(*ChoiceM1), ChoiceE->setTexture(*ChoiceE1), ChoiceI->setTexture(*ChoiceI1), ChoiceF->setTexture(*ChoiceF1);
            
            ChoiceM2->setString("Messor (Hth=180, Stm=60)"), ChoiceE2->setString("Empyreus (Hth=150, Stm=60)"), ChoiceI2->setString("Infernus (Hth=100, Stm=80)"), ChoiceF2->setString("Fridgus (Hth=100, Stm=70)");
            Prompt.setString("Player 1, select your character");
            r1 = Player1.select(mp_x, mp_y);
            
            MW.clear();
            MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(*ChoiceM), MW.draw(*ChoiceE), MW.draw(*ChoiceF), MW.draw(*ChoiceI);
            MW.draw(*ChoiceM2), MW.draw(*ChoiceE2), MW.draw(*ChoiceF2), MW.draw(*ChoiceI2); MW.draw(Prompt);
            MW.draw(*Messor), MW.draw(*Empyreus), MW.draw(*Infernus), MW.draw(*Fridgus);
            MW.display();

            if (r1 == 1 || r1 == 2 || r1 == 3 || r1 == 4) {
                m6 = false; m7 = true;
            }
                
        }
        
        if (m7 == true) {
            ChoiceM2->setString("Messor (Hth=180, Stm=60)"), ChoiceE2->setString("Empyreus (Hth=150, Stm=60)"), ChoiceI2->setString("Infernus (Hth=100, Stm=80)"), ChoiceF2->setString("Fridgus (Hth=100, Stm=70)");
            Prompt.setString("Player 2, select your character");
            r2 = Player2.select(mp_x, mp_y);
        
            if (Player2.counter == 1 && r1 == 1) {
                MW.clear();
                MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(*ChoiceE), MW.draw(*ChoiceF), MW.draw(*ChoiceI);
                MW.draw(*ChoiceE2), MW.draw(*ChoiceF2), MW.draw(*ChoiceI2); MW.draw(Prompt);
                MW.draw(*Empyreus), MW.draw(*Infernus), MW.draw(*Fridgus);
                MW.display();
            }
            else if (Player2.counter == 2 && r1 == 2) {
                MW.clear();
                MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(*ChoiceM), MW.draw(*ChoiceF), MW.draw(*ChoiceI);
                MW.draw(*ChoiceM2), MW.draw(*ChoiceF2), MW.draw(*ChoiceI2); MW.draw(Prompt);
                MW.draw(*Messor), MW.draw(*Infernus), MW.draw(*Fridgus);
                MW.display();
            }
            else if (Player2.counter == 3 && r1 == 3) {
                MW.clear();
                MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(*ChoiceM), MW.draw(*ChoiceE), MW.draw(*ChoiceF);
                MW.draw(*ChoiceM2), MW.draw(*ChoiceE2), MW.draw(*ChoiceF2), MW.draw(Prompt);
                MW.draw(*Messor), MW.draw(*Empyreus), MW.draw(*Fridgus);
                MW.display();
            }
            else if (Player2.counter == 4 && r1 == 4) {
                MW.clear();
                MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(*ChoiceM), MW.draw(*ChoiceE), MW.draw(*ChoiceI);
                MW.draw(*ChoiceM2), MW.draw(*ChoiceE2), MW.draw(*ChoiceI2); MW.draw(Prompt);
                MW.draw(*Messor), MW.draw(*Empyreus), MW.draw(*Infernus);
                MW.display();
            }

            if (r2 == 1 || r2 == 2 || r2 == 3 || r2 == 4) {
                MW.setFramerateLimit(30);
                m7 = false; m8 = true;
                delete CharM, CharE, CharI, CharF, Messor, Empyreus, Infernus, Fridgus;
                delete ChoiceM, ChoiceE, ChoiceI, ChoiceF, ChoiceM1, ChoiceE1, ChoiceI1, ChoiceF1, ChoiceM2, ChoiceE2, ChoiceI2, ChoiceF2;
            } 
        }

        if (m8 == true) {
            A1 = Player1.name + ", your character is: " + Player1.Select.checkname() + "\n" + Player2.name + ", your character is: " + Player2.Select.checkname();
            Prompt.setString(A1);
            temp1 = Player1; temp2 = Player2;

            MW.clear();
            MW.draw(background), MW.draw(Exit), MW.draw(MsgBox), MW.draw(Prompt);
            MW.display();
            Sleep(2500);
            m8 = false, m9 = true;
        }

        if (m9 == true) {
            Player1.setsetTextures(r1); Player2.setsetTextures(r2);
            Player1.textdisplay(), Player2.textdisplay();

            if (Turn1 == true) {
                P1 = Player1.name + ", its your turn \nSelect your attack \nNote: You cannot use heal if \nyour health is above 80%";
                Prompt.setString(P1);
                MW.clear();
                MW.draw(background), MW.draw(Exit), MW.draw(MsgBox); MW.draw(Prompt); MW.draw(Player1.Select.Pic), MW.draw(Player2.Select.Pic);
                MW.draw(Player1.Select.HBar), MW.draw(Player1.Select.SBar), MW.draw(Player2.Select.HBar), MW.draw(Player2.Select.SBar);
                MW.draw(Player1.US), MW.draw(Player2.US), MW.draw(Player1.H), MW.draw(Player1.S), MW.draw(Player2.H), MW.draw(Player2.S);
                MW.draw(Player1.Select.ppp[0].Option); MW.draw(Player1.Select.ppp[1].Option); MW.draw(Player1.Select.ppp[2].Option); MW.draw(Player1.Select.ppp[3].Option);
                MW.draw(Player2.Select.ppp[0].Option); MW.draw(Player2.Select.ppp[1].Option); MW.draw(Player2.Select.ppp[2].Option); MW.draw(Player2.Select.ppp[3].Option);
                MW.draw(Player1.Select.ppp[0].Optiondesc); MW.draw(Player1.Select.ppp[1].Optiondesc); MW.draw(Player1.Select.ppp[2].Optiondesc); MW.draw(Player1.Select.ppp[3].Optiondesc);
                MW.draw(Player2.Select.ppp[0].Optiondesc); MW.draw(Player2.Select.ppp[1].Optiondesc); MW.draw(Player2.Select.ppp[2].Optiondesc); MW.draw(Player2.Select.ppp[3].Optiondesc);
                MW.display();

                temp2.Select = Player1.Select.action(Player2.Select, Player1.check, mp_x, mp_y);
                if (Player1.Select.cc != temp1.Select.cc) {
                    atkmsg.setString(Player1.Select.atkm);
                    Player2 = temp2;
                    Turn1 = false, Turn2 = true;

                    MW.clear();
                    MW.draw(background), MW.draw(Exit), MW.draw(MsgBox); MW.draw(atkmsg); MW.draw(Player1.Select.Pic), MW.draw(Player2.Select.Pic);
                    MW.draw(Player1.Select.HBar), MW.draw(Player1.Select.SBar), MW.draw(Player2.Select.HBar), MW.draw(Player2.Select.SBar);
                    MW.draw(Player1.US), MW.draw(Player2.US), MW.draw(Player1.H), MW.draw(Player1.S), MW.draw(Player2.H), MW.draw(Player2.S);
                    MW.draw(Player1.Select.ppp[0].Option); MW.draw(Player1.Select.ppp[1].Option); MW.draw(Player1.Select.ppp[2].Option); MW.draw(Player1.Select.ppp[3].Option);
                    MW.draw(Player2.Select.ppp[0].Option); MW.draw(Player2.Select.ppp[1].Option); MW.draw(Player2.Select.ppp[2].Option); MW.draw(Player2.Select.ppp[3].Option);
                    MW.draw(Player1.Select.ppp[0].Optiondesc); MW.draw(Player1.Select.ppp[1].Optiondesc); MW.draw(Player1.Select.ppp[2].Optiondesc); MW.draw(Player1.Select.ppp[3].Optiondesc);
                    MW.draw(Player2.Select.ppp[0].Optiondesc); MW.draw(Player2.Select.ppp[1].Optiondesc); MW.draw(Player2.Select.ppp[2].Optiondesc); MW.draw(Player2.Select.ppp[3].Optiondesc);
                    MW.display();
                    Sleep(2500);
                }
         
                if (Player2.Select.health <= 0) {
                    P2 = Player2.name + "'s health is zero \n" + Player1.name + " wins!"; winmsg.setString(P2);
                    m9 = false;
                    MW.clear();
                    MW.draw(background), MW.draw(Exit), MW.draw(WinBox), MW.draw(winmsg);
                    MW.display();
                }
            }
            else if (Turn2 == true) {
                P2 = Player2.name + ", its your turn \nSelect your attack \nNote: You cannot use heal if \nyour health is above 80%";
                Prompt.setString(P2);
                MW.clear();
                MW.draw(background), MW.draw(Exit), MW.draw(MsgBox); MW.draw(Prompt); MW.draw(Player1.Select.Pic), MW.draw(Player2.Select.Pic);
                MW.draw(Player1.Select.HBar), MW.draw(Player1.Select.SBar), MW.draw(Player2.Select.HBar), MW.draw(Player2.Select.SBar);
                MW.draw(Player1.US), MW.draw(Player2.US), MW.draw(Player1.H), MW.draw(Player1.S), MW.draw(Player2.H), MW.draw(Player2.S);
                MW.draw(Player1.Select.ppp[0].Option); MW.draw(Player1.Select.ppp[1].Option); MW.draw(Player1.Select.ppp[2].Option); MW.draw(Player1.Select.ppp[3].Option);
                MW.draw(Player2.Select.ppp[0].Option); MW.draw(Player2.Select.ppp[1].Option); MW.draw(Player2.Select.ppp[2].Option); MW.draw(Player2.Select.ppp[3].Option);
                MW.draw(Player1.Select.ppp[0].Optiondesc); MW.draw(Player1.Select.ppp[1].Optiondesc); MW.draw(Player1.Select.ppp[2].Optiondesc); MW.draw(Player1.Select.ppp[3].Optiondesc);
                MW.draw(Player2.Select.ppp[0].Optiondesc); MW.draw(Player2.Select.ppp[1].Optiondesc); MW.draw(Player2.Select.ppp[2].Optiondesc); MW.draw(Player2.Select.ppp[3].Optiondesc);
                MW.display();

                temp1.Select = Player2.Select.action(Player1.Select, Player2.check, mp_x, mp_y);
                if (Player2.Select.cc != temp2.Select.cc) {
                    atkmsg.setString(Player2.Select.atkm);
                    Player1 = temp1;
                    Turn2 = false, Turn1 = true;

                    MW.clear();
                    MW.draw(background), MW.draw(Exit), MW.draw(MsgBox); MW.draw(atkmsg); MW.draw(Player1.Select.Pic), MW.draw(Player2.Select.Pic);
                    MW.draw(Player1.Select.HBar), MW.draw(Player1.Select.SBar), MW.draw(Player2.Select.HBar), MW.draw(Player2.Select.SBar);
                    MW.draw(Player1.US), MW.draw(Player2.US), MW.draw(Player1.H), MW.draw(Player1.S), MW.draw(Player2.H), MW.draw(Player2.S);
                    MW.draw(Player1.Select.ppp[0].Option); MW.draw(Player1.Select.ppp[1].Option); MW.draw(Player1.Select.ppp[2].Option); MW.draw(Player1.Select.ppp[3].Option);
                    MW.draw(Player2.Select.ppp[0].Option); MW.draw(Player2.Select.ppp[1].Option); MW.draw(Player2.Select.ppp[2].Option); MW.draw(Player2.Select.ppp[3].Option);
                    MW.draw(Player1.Select.ppp[0].Optiondesc); MW.draw(Player1.Select.ppp[1].Optiondesc); MW.draw(Player1.Select.ppp[2].Optiondesc); MW.draw(Player1.Select.ppp[3].Optiondesc);
                    MW.draw(Player2.Select.ppp[0].Optiondesc); MW.draw(Player2.Select.ppp[1].Optiondesc); MW.draw(Player2.Select.ppp[2].Optiondesc); MW.draw(Player2.Select.ppp[3].Optiondesc);
                    MW.display();
                    Sleep(2500);
                }

                if (Player1.Select.health <= 0) {
                    P1 = Player1.name + "'s health is zero \n" + Player2.name + " wins!"; winmsg.setString(P1);
                    m9 = false;
                    MW.clear();
                    MW.draw(background), MW.draw(Exit), MW.draw(WinBox), MW.draw(winmsg);
                    MW.display();
                }
            }
        }       
    }
    return 0;
}
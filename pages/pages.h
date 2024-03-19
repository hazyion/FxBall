#ifndef PAGES_H
#define PAGES_H

#include<SFML/Graphics.hpp>
#include"../class/CustomClasses.h"

void menu(sf::RenderWindow* window, sf::Font logoFont, sf::Font normFont);
int game(sf::RenderWindow* window, sf::Font normFont);
int howto(sf::RenderWindow* window, sf::Font normFont);
int credits(sf::RenderWindow* window, sf::Font normFont);
int pause(sf::RenderWindow* window, sf::Font logoFont, sf::Font normFont);
int level(sf::RenderWindow* window, sf::Font normFont, LevelData* level);
int levelSelect(sf::RenderWindow* window, sf::Font normFont);

LevelData l1(int windowWidth, int windowHeight);
LevelData l2(int windowWidth, int windowHeight);

#endif

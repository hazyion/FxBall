#include<SFML/Graphics.hpp>
#include<iostream>
#include<unistd.h>
#include"pages.h"

int credits(sf::RenderWindow* window, sf::Font normFont){
  int windowWidth = window->getSize().x, windowHeight = window->getSize().y;

  sf::Text startText, quitText, creditsText, logoText, howtoText, logoTextbg;
  std::vector<std::string> lines = {
    "Created by Carl Jason",
    "This game is free to be used, modified and distributed commerically",
    "All assets used in the game are not necessarily free for commercial use",
  };
  std::vector<sf::Text> textArr(lines.size(), sf::Text("", normFont, 40));

  int initPad = windowHeight / lines.size(), lineGap = windowHeight / (lines.size() + 2);

  for(int i = 0; i < textArr.size(); i++){
    textArr[i].setString(lines[i]);
    textArr[i].setOrigin(textArr[i].getLocalBounds().width / 2, textArr[i].getLocalBounds().height / 2);
    textArr[i].setPosition((float)windowWidth / 2, initPad + lineGap * i);
  }

  sf::Text escText("Press ESC to go back", normFont, 25); 
  escText.setPosition(80, 80);
  escText.setFillColor(sf::Color::Green);

  while(window->isOpen()){
    usleep(5000);
    sf::Event event;
    while(window->pollEvent(event)){
      if(event.type == sf::Event::Closed){
        window->close();
      }

      if(event.type == sf::Event::KeyPressed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
          return 3;
        }
      }
    }

    window->clear();
    for(int i = 0; i < textArr.size(); i++){
      window->draw(textArr[i]);
    }
    window->draw(escText);
    window->display();
  }
  return -1;
}

#include<SFML/Graphics.hpp>
#include<iostream>
#include<unistd.h>
#include"pages.h"

int howto(sf::RenderWindow* window, sf::Font normFont){
  int windowWidth = window->getSize().x, windowHeight = window->getSize().y;

  std::vector<std::string> lines = {
    "The objective of the game is to get rid of all the bricks.",
    "Bounce the ball on the bounce pad to send it back towards the bricks.",
    "Use the left and right arrow keys to move the bouncepad.",
    "The further away from the center of the bouncepad, the more the ball bounces outward.",
    "If all the balls disappear off the screen, the game ends."
  };
  std::vector<sf::Text> textArr(lines.size(), sf::Text("", normFont, 40));

  int initPad = windowHeight / lines.size(), lineGap = (windowHeight - initPad) / (lines.size() + 1);

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

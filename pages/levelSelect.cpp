#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<unistd.h>
#include<iostream>
#include"pages.h"

int levelSelect(sf::RenderWindow* window, sf::Font normFont){
  int windowWidth = window->getSize().x, windowHeight = window->getSize().y;

  sf::RectangleShape levelbg(sf::Vector2f(120, 120));
  levelbg.setOrigin(levelbg.getSize().x / 2, levelbg.getSize().y / 2);
  levelbg.setFillColor(sf::Color::Yellow);

  sf::SoundBuffer menuSelectBuffer;
  if(!menuSelectBuffer.loadFromFile("assets/menuselect.wav")){
    std::cout<<"Error loading audio"<<std::endl;
    return -1;
  }

  sf::Sound menuSelect;
  menuSelect.setBuffer(menuSelectBuffer);
  menuSelect.setVolume(60);

  sf::Text escText("Press ESC to go back", normFont, 25); 
  escText.setPosition(80, 80);
  escText.setFillColor(sf::Color::Green);

  int levelCount = 2;
  sf::Text levelHeader("Select Level", normFont, 65);
  levelHeader.setPosition(150, 150);
  levelHeader.setFillColor(sf::Color::White);

  std::vector<sf::Text> levelsArr(levelCount, sf::Text("", normFont, 100));
  for(int i = 0; i < levelCount; i++){
    levelsArr[i].setString(std::to_string(i+1));
    levelsArr[i].setOrigin(levelsArr[i].getLocalBounds().width / 2, levelsArr[i].getLocalBounds().height / 2);
    levelsArr[i].setPosition((float)windowWidth * (i + 1) / (levelCount + 1), (float)windowHeight / 2);
  }

  int selectedLevel = 0;
  while(window->isOpen()){
    usleep(5000);
    sf::Event event;
    while(window->pollEvent(event)){
      if(event.type == sf::Event::Closed){
        window->close();
      }

      if(event.type == sf::Event::KeyPressed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
          selectedLevel -= 1;
          selectedLevel += levelCount;
          selectedLevel %= levelCount;
          menuSelect.play();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
          selectedLevel += 1;
          selectedLevel %= levelCount;
          menuSelect.play();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
          return 101 + selectedLevel;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
          return 3;
        }
      }
    }

    window->clear();

    window->draw(levelHeader);
    for(int i = 0; i < levelsArr.size(); i++){
      if(i == selectedLevel){
        levelsArr[i].setFillColor(sf::Color::Black);
        levelbg.setPosition(levelsArr[i].getPosition().x, levelsArr[i].getPosition().y + 40);

        window->draw(levelbg);
      }
      else{
        levelsArr[i].setFillColor(sf::Color::White);
      }
      window->draw(levelsArr[i]);
    }
    window->draw(escText);
    window->display();
  }
  return -1;
}

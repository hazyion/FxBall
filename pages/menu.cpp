#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<stack>
#include<unistd.h>
#include"pages.h"

void pushUpdate(int* ps, int* gs, int ret, std::stack<int>* stack){
  *ps = *gs;
  stack->push(*gs);
  *gs = ret;
}

void menu(sf::RenderWindow* window, sf::Font logoFont, sf::Font normFont){
  int windowWidth = window->getSize().x, windowHeight = window->getSize().y;

  // gameState mapping
  //
  // -1 - End Game
  // 0 - Menu
  // 1 - Level Select
  // 2 - How To Play
  // 3 - Escape
  // 4 - credits
  // 5 - pause
  // 1xx - level xx

  std::stack<int> gameStateStack;
  gameStateStack.push(-1);

  sf::Text logoText, logoTextbg;
  std::vector<std::string> lines = {
    "Start",
    "How to Play",
    "Credits",
    "Quit"
  };
  std::vector<sf::Text> textArr(lines.size(), sf::Text("", normFont, 45)), selectorArr(lines.size(), sf::Text(">", normFont, 45));

  int initPad = windowHeight * 2 / 5, lineGap = (windowHeight - initPad) / (lines.size() + 1);

  for(int i = 0; i < textArr.size(); i++){
    textArr[i].setString(lines[i]);
    textArr[i].setPosition((float)windowWidth / 8, initPad + lineGap * i);

    selectorArr[i].setPosition((float)windowWidth / 8 - 30, initPad + lineGap * i);
    selectorArr[i].setStyle(sf::Text::Bold);
  }

  logoText.setFont(logoFont);
  logoText.setCharacterSize(75);
  logoText.setString("FXBall");
  logoText.setOrigin(logoText.getLocalBounds().width / 2, logoText.getLocalBounds().height / 2);
  logoText.setPosition((float)windowWidth / 2, 150);
  logoText.setFillColor(sf::Color::Red);

  logoTextbg.setFont(logoFont);
  logoTextbg.setCharacterSize(75);
  logoTextbg.setString("FXBall");
  logoTextbg.setOrigin(logoText.getLocalBounds().width / 2, logoText.getLocalBounds().height / 2);
  logoTextbg.setPosition((float)windowWidth / 2 + 4, 150 + 4);
  logoTextbg.setFillColor(sf::Color::Yellow);

  // selection is the current selection in menu
  LevelData lData;
  int selection = 0, gameState = 0, prevState = -1;
  int ret;

  while(window->isOpen()){
    usleep(5000);
    sf::Event event;
    while(window->pollEvent(event)){
      if(event.type == sf::Event::Closed){
        window->close();
      }

      if(event.type == sf::Event::KeyPressed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
          selection += 1;
          selection %= textArr.size();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
          selection -= 1;
          selection %= textArr.size();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
          switch(selection){
            case 0:
              pushUpdate(&prevState, &gameState, 1, &gameStateStack);
              break;
            case 1:
              pushUpdate(&prevState, &gameState, 2, &gameStateStack);
              break;
            case 2:
              pushUpdate(&prevState, &gameState, 4, &gameStateStack);
              break;
            case 3:
              return;
          }
        }
      }
    }

    if(gameState == 0){
      window->clear();
      for(int i = 0; i < textArr.size(); i++){
        window->draw(textArr[i]);
      }
      window->draw(selectorArr[selection]);
      window->draw(logoTextbg);
      window->draw(logoText);
      window->display();
    }

    switch(gameState){
      case 0:
        break;
      case 1:
        ret = levelSelect(window, normFont);
        if(ret >= 100){
          pushUpdate(&prevState, &gameState, ret, &gameStateStack);
        }
        else if(ret == 3){
          gameState = gameStateStack.top();
          gameStateStack.pop();
        }
        break;
      case 2:
        ret = howto(window, normFont);
        if(ret == 3){
          gameState = gameStateStack.top();
          gameStateStack.pop();
        }
        else if(ret == -1){
          gameState = -1;
        }
        break;
      case 3:
        gameState = gameStateStack.top();
        gameStateStack.pop();
        break;
      case 4:
        ret = credits(window, normFont);
        if(ret == 3){
          gameState = gameStateStack.top();
          gameStateStack.pop();
        }
        else if(ret == -1){
          gameState = -1;
        }
        break;
      case 5:
        ret = pause(window, logoFont, normFont);
        if(ret == 3){
          gameState = gameStateStack.top();
          gameStateStack.pop();
        }
        else if(ret == 1 || ret == 0){
          pushUpdate(&prevState, &gameState, ret, &gameStateStack);
        }
        else if(ret == -1){
          gameState = -1;
        }
        break;
      case -1:
        return;
      default:{
        int levelNo = gameState - 100;
        switch(levelNo){
          case 1:
            if(prevState == 1){
              lData = l1(windowWidth, windowHeight);
            } 
            break;
          case 2:
            if(prevState == 1){
              lData = l2(windowWidth, windowHeight);
            }
            break;
        }
        ret = level(window, normFont, &lData);
        pushUpdate(&prevState, &gameState, ret, &gameStateStack);
        break;
      }
    }
  }
  return;
}

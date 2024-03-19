#include<SFML/Graphics.hpp>
#include"pages.h"

int pause(sf::RenderWindow* window, sf::Font logoFont, sf::Font normFont){
  int windowWidth = window->getSize().x, windowHeight = window->getSize().y; 

  sf::Text logoText, logoTextbg;
  std::vector<std::string> lines = {
    "Continue",
    "Change Level",
    "Exit to Menu",
    "Quit Game"
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
  logoText.setCharacterSize(60);
  logoText.setString("DXBall");
  logoText.setPosition((float)windowWidth / 8, (float)initPad / 2);
  logoText.setFillColor(sf::Color::Red);

  logoTextbg.setFont(logoFont);
  logoTextbg.setCharacterSize(60);
  logoTextbg.setString("DXBall");
  logoTextbg.setPosition((float)windowWidth / 8 + 4, (float)initPad / 2 + 4);
  logoTextbg.setFillColor(sf::Color::Yellow);

  int pauseSelection = 0;
  while(window->isOpen()){

    // Event loop
    sf::Event event;
    while(window->pollEvent(event)){
      switch(event.type){
        case sf::Event::Closed:
          window->close();
          break;

        case sf::Event::KeyPressed:
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            pauseSelection += 1;
            pauseSelection %= textArr.size();
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            pauseSelection -= 1;
            pauseSelection %= textArr.size();
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            switch(pauseSelection){
              case 0:
                return 3;
              case 1:
                return 1;
              case 2:
                return 0;
              case 3:
                return -1;
              default:
                return pauseSelection;
            }
          }

          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return 3;
          }     
          break;

          default:
            break;
      }
    }

    window->clear();
    for(int i = 0; i < textArr.size(); i++){
      if(i == pauseSelection){
        window->draw(selectorArr[i]);
      }
      window->draw(textArr[i]);
    }

    window->draw(logoTextbg);
    window->draw(logoText);
    window->display();
  }
  return -1;
}

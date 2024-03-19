#include<SFML/Graphics.hpp>
#include<unistd.h>
#include<iostream>
#include"pages/pages.h"

int main(){
  int windowWidth = 1800, windowHeight = 900;
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "DxBall");

  sf::Font normFont, logoFont;
  if(!normFont.loadFromFile("assets/b2bsporty.otf")){
    std::cout<<"Error loading font\n";
    return -1;
  }

  if(!logoFont.loadFromFile("assets/logofont.ttf")){
    std::cout<<"Error loading font\n";
    return -1;
  }
  
  menu(&window, logoFont, normFont);

  return 0;
}

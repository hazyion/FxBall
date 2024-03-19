#include"CustomClasses.h"

Brick::Brick(sf::Vector2f wh, int diff): sf::RectangleShape(wh){
    this->difficulty = diff;
    setColor(diff);
  }

void Brick::setColor(int diff){
  switch(diff){
    case 1:
      this->setFillColor(sf::Color::White);
      break;

    case 2:
      this->setFillColor(sf::Color::Yellow);
      break;

    case 3:
      this->setFillColor(sf::Color::Red);
      break;
  }
}

void Brick::setDifficulty(int diff){
  this->difficulty = diff;
  setColor(diff);
}

int Brick::getDifficulty(){
  return this->difficulty;
}


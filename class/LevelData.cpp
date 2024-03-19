#include"CustomClasses.h"

LevelData::LevelData(std::vector<Brick> bricks, std::vector<Ball> balls, sf::RectangleShape bouncepad, int brickWidth, int brickHeight, float ballRadius){
  this->bricks = bricks;
  this->balls = balls;
  this->bouncepad = bouncepad;
  this->brickWidth = brickWidth;
  this->brickHeight = brickHeight;
  this->ballRadius = ballRadius;
}

LevelData::LevelData(){};

#include<SFML/Graphics.hpp>
#include"../class/CustomClasses.h"
#include"../pages/pages.h"

LevelData l1(int windowWidth, int windowHeight){
  std::vector<Brick> bricks;

  // Brick Layout Generation
  int highBrickCount = 11, lowBrickCount = 8;
  float brickWidth = (float)windowWidth / 25, brickHeight = (float)windowHeight / 22;
  float totalGapX = (float)windowWidth - highBrickCount * brickWidth;
  float gapX = 50;
  float offsetX = (totalGapX - gapX * (highBrickCount - 1)) / 2;
  float gapY = 1.5 * brickHeight;
  float curX = offsetX;

  for(int i = 0; i < highBrickCount; i++){
    Brick newBrick(sf::Vector2f(brickWidth, brickHeight), 2);
    newBrick.setPosition(curX, 50);
    bricks.push_back(newBrick); 

    newBrick.setPosition(curX, 50 + 2 * (brickHeight + gapY));
    newBrick.setDifficulty(3);
    bricks.push_back(newBrick);
    
    curX += brickWidth + gapX;
  }

  totalGapX = (float)windowWidth - lowBrickCount * brickWidth;
  offsetX = (totalGapX - gapX * (lowBrickCount - 1)) / 2;
  curX = offsetX;

  for(int i = 0; i < lowBrickCount; i++){
    Brick newBrick(sf::Vector2f(brickWidth, brickHeight), 1);
    newBrick.setPosition(curX, 50 + brickHeight + gapY);
    bricks.push_back(newBrick); 
    
    curX += brickWidth + gapX;
  }

  // Bouncepad
  int bouncepadWidth = 210, bouncepadHeight = 20;
  sf::RectangleShape bouncepad(sf::Vector2f(bouncepadWidth, bouncepadHeight));
  sf::Vector2f bouncepadPosition((float)windowWidth / 1.6, (float)windowHeight * 0.8);
  bouncepad.setPosition(bouncepadPosition);

  // Balls
  float ballRadius = 16.f;
  std::vector<Ball> balls = {Ball(ballRadius)};
  balls[0].setPosition(800, 400);

  return LevelData(bricks, balls, bouncepad, brickWidth, brickHeight, ballRadius);
}

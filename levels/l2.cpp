#include<SFML/Graphics.hpp>
#include"../class/CustomClasses.h"

LevelData l2(int windowWidth, int windowHeight){
  std::vector<Brick> bricks;

  // Brick Layout Generation
  float brickWidth = (float)windowWidth / 25, brickHeight = (float)windowHeight / 22;
  float totalGapX = (float)windowWidth - 15 * brickWidth;
  float gapX = 30;
  float offsetX = (totalGapX - gapX * (15 - 1)) / 2;
  float gapY = 0.75 * brickHeight;
  float curX = offsetX;

  for(int i = 0; i < 15; i++){
    Brick newBrick(sf::Vector2f(brickWidth, brickHeight), 2);
    newBrick.setPosition(curX, 50);
    bricks.push_back(newBrick); 

    newBrick.setPosition(curX, 50 + 2 * (brickHeight + gapY));
    newBrick.setDifficulty(3);
    bricks.push_back(newBrick);
    
    curX += brickWidth + gapX;
  }

  totalGapX = (float)windowWidth - 12 * brickWidth;
  offsetX = (totalGapX - gapX * (12 - 1)) / 2;
  curX = offsetX;

  for(int i = 0; i < 12; i++){
    Brick newBrick(sf::Vector2f(brickWidth, brickHeight), 1);
    newBrick.setPosition(curX, 50 + brickHeight + gapY);
    bricks.push_back(newBrick); 
    
    curX += brickWidth + gapX;
  }

  // Bouncepad
  int bouncepadWidth = 210, bouncepadHeight = 20;
  sf::RectangleShape bouncepad(sf::Vector2f(bouncepadWidth, bouncepadHeight));
  sf::Vector2f bouncepadPosition((float)windowWidth / 1.5, (float)windowHeight * 0.8);
  bouncepad.setPosition(bouncepadPosition);
  bouncepad.setFillColor(sf::Color::Cyan);

  // Balls
  float ballRadius = 13.f;
  std::vector<Ball> balls = {Ball(ballRadius)};
  balls[0].setFillColor(sf::Color::Yellow);
  balls[0].setPosition(650, 500);

  return LevelData(bricks, balls, bouncepad, brickWidth, brickHeight, ballRadius);
}

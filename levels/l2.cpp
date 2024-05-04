#include<SFML/Graphics.hpp>
#include"../class/CustomClasses.h"
#include"../pages/pages.h"

LevelData l2(int windowWidth, int windowHeight){
  std::vector<Brick> bricks;

  // Brick Layout Generation
  float brickWidth = (float)windowWidth / 25, brickHeight = (float)windowHeight / 22;
  int rows = 5, gapY = windowHeight / 20, gapX = windowWidth / 20, initPad = 30;
  for(int i = 0; i < rows; i++){
    if(i <= rows / 2){
      int max = i*2 + 1;
      for(int j = 0; j < max; j++){
        Brick newBrick({brickWidth, brickHeight}, 3 - i);
        newBrick.setPosition(
          windowWidth / 2 - brickWidth / 2 - (j - (int)(max / 2)) * (brickWidth + gapX),
          (float)(initPad + (i+1) * (gapY + brickHeight))
        );
        bricks.push_back(newBrick);
      }
    }
    else if(i > rows / 2){
      int start = (rows-i-1) * 2 + 1;
      for(int j = start; j > 0; j--){
        Brick newBrick({brickWidth, brickHeight}, 3 - (rows-i-1));
        newBrick.setPosition(
          windowWidth / 2 - brickWidth / 2 - (j - (int)(start / 2) - 1) * (brickWidth + gapX),
          (float)(initPad + (i+1) * (gapY + brickHeight))
        );
        bricks.push_back(newBrick);
      }
    }
  }

  // Bouncepad
  int bouncepadWidth = 210, bouncepadHeight = 20;
  sf::RectangleShape bouncepad(sf::Vector2f(bouncepadWidth, bouncepadHeight));
  sf::Vector2f bouncepadPosition((float)windowWidth / 2.2, (float)windowHeight * 0.8);
  bouncepad.setPosition(bouncepadPosition);

  // Balls
  float ballRadius = 16.f;
  std::vector<Ball> balls = {Ball(ballRadius)};
  balls[0].setPosition(550, 400);

  return LevelData(bricks, balls, bouncepad, brickWidth, brickHeight, ballRadius);
}

#ifndef CUSTOM_CLASSES_H
#define CUSTOM_CLASSES_H

#include<SFML/Graphics.hpp>

class Ball: public sf::CircleShape{
  public:
    float speed;
    float angle;
  
    Ball(float radius);
};


class Brick: public sf::RectangleShape{
  private:
    int difficulty = 1;

  public:
    Brick(sf::Vector2f wh, int diff);
    void setColor(int diff);
    void setDifficulty(int diff);
    int getDifficulty();
};

class LevelData{
  public:
    std::vector<Brick> bricks;
    std::vector<Ball> balls;
    sf::RectangleShape bouncepad;
    int brickWidth, brickHeight;
    float ballRadius;

    LevelData(std::vector<Brick> bricks, std::vector<Ball> balls, sf::RectangleShape bouncepad, int brickWidth, int brickHeight, float ballRadius);

    LevelData();
};

#endif

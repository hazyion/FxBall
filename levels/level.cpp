#include<SFML/Graphics.hpp>
#include <cstdlib>
#include<iostream>
#include<cmath>
#include<unistd.h>
#include"../class/CustomClasses.h"
#include"../pages/pages.h"

int level(sf::RenderWindow* window, sf::Font normFont, LevelData* level){
  int windowWidth = window->getSize().x, windowHeight = window->getSize().y;
  sf::Clock clock;
  bool isKeyPressed = false;
  sf::Event keyPressEvent;
  sf::Int64 totalTime = 0;

  std::vector<Brick>* bricks = &level->bricks;
  std::vector<Ball>* balls = &level->balls;
  sf::RectangleShape* bouncepad = &level->bouncepad;
  sf::Vector2f bouncepadPosition = bouncepad->getPosition();
  float ballRadius = level->ballRadius;
  int brickHeight = level->brickHeight, brickWidth = level->brickWidth;

  sf::Text endText("", normFont, 70), enterText("Press ENTER to Continue", normFont, 25);
  enterText.setOrigin(enterText.getLocalBounds().width / 2, enterText.getLocalBounds().height / 2);
  enterText.setPosition((float)windowWidth / 2, (float)windowHeight / 2 + 60);

  sf::Texture brickTexture;
  if(!brickTexture.loadFromFile("assets/brick.png")){
    std::cout<<"Error loading texture"<<std::endl;
    return -1;
  }

  sf::Texture ballTexture;
  if(!ballTexture.loadFromFile("assets/ball.png")){
    std::cout<<"Error loading texture"<<std::endl;
    return -1;
  }

  for(int i = 0; i < level->bricks.size(); i++){
    level->bricks[i].setTexture(&brickTexture);
  }

  for(int i = 0; i < level->balls.size(); i++){
    level->balls[i].setTexture(&ballTexture);
  }

  sf::Texture bouncepadTexture;
  if(!bouncepadTexture.loadFromFile("assets/bouncepad.png")){
    std::cout<<"Error loading texture"<<std::endl;
    return -1;
  }
  level->bouncepad.setTexture(&bouncepadTexture);

  bool gameEnd = false;

  while(window->isOpen()){

    // Event loop
    sf::Event event;
    while(window->pollEvent(event)){
      switch(event.type){
        case sf::Event::Closed:
          window->close();
          break;

        case sf::Event::KeyPressed:
          isKeyPressed = true;
          keyPressEvent = event;
          if(event.key.code == sf::Keyboard::Escape && !gameEnd){
            return 5;
          }
          else if(event.key.code == sf::Keyboard::Enter && gameEnd){
            return 0;
          }
          break;

        case sf::Event::KeyReleased:
          if(event.key.code == keyPressEvent.key.code)
            isKeyPressed = false;
          break;

        default:
          break;
      }
    }

    sf::Int64 elapsedTime = clock.restart().asMicroseconds();
    totalTime += elapsedTime;

    if(!gameEnd){
    // Update bouncepad position
      if(isKeyPressed){
        if(keyPressEvent.key.code == sf::Keyboard::Left && bouncepadPosition.x > 15){
          bouncepadPosition.x -= (float)elapsedTime * windowWidth / (1000000 * 4);
          bouncepad->setPosition(bouncepadPosition);
        }

        if(keyPressEvent.key.code == sf::Keyboard::Right && bouncepadPosition.x < windowWidth - 15 - bouncepad->getSize().x){
          bouncepadPosition.x += (float)elapsedTime * windowWidth / (1000000 * 4);
          bouncepad->setPosition(bouncepadPosition);
        }
      }

      // Ball position update
      std::vector<Ball> leftBalls;
      for(int i = 0; i < balls->size(); i++){
        sf::Vector2f ballPos = balls->at(i).getPosition();
        
        float speedX = balls->at(i).speed * cos(balls->at(i).angle * M_PI / 180);
        float speedY = balls->at(i).speed * sin(balls->at(i).angle * M_PI / 180);

        // Bouncepad collision
        auto ballBoundingBox = balls->at(i).getGlobalBounds();
        if(speedY > 0 && ballBoundingBox.intersects(bouncepad->getGlobalBounds())){
          float ballMid = ballPos.x + ballRadius,
            bpadMid = bouncepadPosition.x + bouncepad->getSize().x / 2;
          int xDiff = fabs(ballMid - bpadMid);

          speedY *= -1;
          balls->at(i).angle = atan2(speedY, speedX) * 180 / M_PI;

          if(ballMid > bpadMid){
            balls->at(i).angle += xDiff / (bouncepad->getSize().x / 2) * 20;
          }
          else{
            balls->at(i).angle -= xDiff / (bouncepad->getSize().x / 2) * 20;
          }

          speedX = balls->at(i).speed * cos(balls->at(i).angle * M_PI / 180);
          speedY = balls->at(i).speed * sin(balls->at(i).angle * M_PI / 180);
        }

        // Side wall collision
        if(ballPos.x <= 0 && speedX < 0 ||
          ballPos.x >= windowWidth - 2 * ballRadius && speedX > 0){
          speedX *= -1;
        }

        // Upper wall collision
        if(ballPos.y <= 0 && speedY < 0){
          speedY *= -1;
        }

        // Brick collision
        for(auto bIter = bricks->begin(); bIter != bricks->end(); bIter++){
          Brick brick = *bIter;
          if(ballBoundingBox.intersects(brick.getGlobalBounds())){

            // Left
            if(ballPos.x < brick.getPosition().x &&
              ballPos.y > brick.getPosition().y - ballRadius &&
              ballPos.y < brick.getPosition().y + brickHeight - ballRadius &&
              speedX > 0){
              speedX *= -1;
              bIter->setDifficulty(brick.getDifficulty() - 1);
              std::iter_swap(bIter, bricks->end() - 1);
            }
            
            // Right
            else if(ballPos.x > brick.getPosition().x &&
              ballPos.y > brick.getPosition().y - ballRadius &&
              ballPos.y < brick.getPosition().y + brickHeight - ballRadius &&
              speedX < 0){
              speedX *= -1;
              bIter->setDifficulty(brick.getDifficulty() - 1);
              std::iter_swap(bIter, bricks->end() - 1);
            }

            // Top
            else if(ballPos.y < brick.getPosition().y &&
              ballPos.x > brick.getPosition().x - ballRadius &&
              ballPos.x < brick.getPosition().x + brickWidth - ballRadius &&
              speedY > 0){
              speedY *= -1;
              bIter->setDifficulty(brick.getDifficulty() - 1);
              std::iter_swap(bIter, bricks->end() - 1);
            }

            // Bottom
            else if(ballPos.y > brick.getPosition().y &&
              ballPos.x > brick.getPosition().x - ballRadius &&
              ballPos.x < brick.getPosition().x + brickWidth - ballRadius &&
              speedY < 0){
              speedY *= -1;
              bIter->setDifficulty(brick.getDifficulty() - 1);
              std::iter_swap(bIter, bricks->end() - 1);
            }

            break;
          }
        }
        if(! (--bricks->end())->getDifficulty()){
          bricks->pop_back();
        }

        ballPos.x += (float)elapsedTime * speedX / 1000000;
        ballPos.y += (float)elapsedTime * speedY / 1000000;

        balls->at(i).setPosition(ballPos);

        balls->at(i).angle = atan2(speedY, speedX) * 180 / M_PI;

        if(ballPos.y <= windowHeight){
          leftBalls.push_back(balls->at(i));
        }
        else{
          continue;
        }
      }
      *balls = leftBalls;

      if(!balls->size()){
        endText.setString("LEVEL FAILED");
        endText.setFillColor(sf::Color::Red);
        endText.setOrigin(endText.getLocalBounds().width / 2, endText.getLocalBounds().height / 2);
        endText.setPosition((float)windowWidth / 2, (float)windowHeight / 2 - 60);
        gameEnd = true;
      }

      else if(!bricks->size()){
        endText.setString("LEVEL COMPLETED");
        endText.setFillColor(sf::Color::Green);
        endText.setOrigin(endText.getLocalBounds().width / 2, endText.getLocalBounds().height / 2);
        endText.setPosition((float)windowWidth / 2, (float)windowHeight / 2 - 60);
        gameEnd = true;
      }
    }

    // Clear and draw
    window->clear(sf::Color::Black);
    for(auto brick: *bricks){
      window->draw(brick);
    }

    if(gameEnd){
      window->draw(endText);
      window->draw(enterText);
    }

    for(auto ball: *balls){
      window->draw(ball);
    }
    window->draw(*bouncepad);
    window->display();
  }
  return -1;
}

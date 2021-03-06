#include <iostream>
#include <cmath>
#include "sprite.h"
#include "gamedata.h"

int getRandomFactor() {
	int number = Gamedata::getInstance()->getRandInRange(50, 80);
	number *= rand() % 2 ? -1 : 1;
	return number;
}

Sprite::Sprite(const std::string& name, const Frame* const frame) :
  Drawable(name,
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance()->getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"/speedX")+getRandomFactor(), 
                    Gamedata::getInstance()->getXmlInt(name+"/speedY")+getRandomFactor()) 
           ),
  frame( frame ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance()->getXmlInt("world/height"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s),
  frame(s.frame),  // shallow copy; Manager may reuse it
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance()->getXmlInt("world/height"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=(rhs);
  frame = rhs.frame;  // shallow copy; Manager may reuse it
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
  velocityY( -velocityY() );
  }
  if ( Y() > worldHeight-frameHeight) {
	velocityY( -velocityY() );
  }

  if ( X() < 0) {
    velocityX( -velocityX() );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -velocityX() );
  }  
}

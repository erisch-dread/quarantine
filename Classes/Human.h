#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "cocos2d.h"
#include <string>

#define WANDER_ZERO_ODDS 75 //%
#define SPEED 1

class Human
{
	//TODO: _spd, _infected
	private:
		cocos2d::Sprite *_sprite;
		//cocos2d::Point 	_spd;
		float			_spd;
		std::string		_normalSprite,
						_infectedSprite;
		bool			_infected;

	public:
		Human(std::string normal, cocos2d::Point pos, cocos2d::Layer *layer);
		Human(std::string normal, std::string infected, cocos2d::Point, cocos2d::Layer*);
		
		void			setPosition(cocos2d::Point);
		void			setPosition(cocos2d::Point, cocos2d::TMXLayer *meta);
		cocos2d::Point	getPosition();

		//void			setSpeed(cocos2d::Point);
		//cocos2d::Point	getSpeed();
		void			setSpeed(float newSpd);
		float			getSpeed();


		void			infect();
		bool			isInfected();

		bool			collidesWithSprite(cocos2d::Sprite *target);
		bool			collidesWith(Human *target);

		cocos2d::Rect	getBoundingBox();
		cocos2d::Size 	getContentSize();

		//Now for the fun methods
		cocos2d::Point	wander();
		cocos2d::Point	moveFrom(cocos2d::Point);
		cocos2d::Point	moveToward(cocos2d::Point);
		cocos2d::Point	moveLeft();
		cocos2d::Point	moveRight();
		cocos2d::Point	moveUp();
		cocos2d::Point	moveDown();
};

#endif // __HUMAN_H__
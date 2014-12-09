#include "Human.h"

Human::Human(std::string path, cocos2d::Point pos, cocos2d::Layer *layer){
	_normalSprite = path;
	_infectedSprite = path;
	_infected = false;

	_sprite = cocos2d::Sprite::create(path);
	_sprite->setPosition(pos);

	layer->addChild(_sprite);	
}

Human::Human(std::string pathToNormal, std::string pathToInfected, cocos2d::Point pos, cocos2d::Layer *layer){
	_normalSprite = pathToNormal;
	_infectedSprite = pathToInfected;
	_infected = false;

	_sprite = cocos2d::Sprite::create(_normalSprite);

	layer->addChild(_sprite);
}

void Human::setPosition(cocos2d::Point pos){
	_sprite->setPosition(pos);
}

//void Human::setPosition(cocos2d::Point pos, cocos2d::TMXLayer *meta){
//	meta->setTileGID(1,_sprite->getPosition());
//	_sprite->setPosition(pos);
//	meta->setTileGID(0, pos);
//}

cocos2d::Point Human::getPosition(){
	return _sprite->getPosition();
}

void Human::setSpeed(cocos2d::Point spd){
	_spd = spd;
}

cocos2d::Point Human::getSpeed(){
	return _spd;
}

void Human::infect(){
	_infected = true;
	_sprite->setTexture(cocos2d::TextureCache::sharedTextureCache()->addImage("sprites/cootiedjigglybit.png"));
}

bool Human::isInfected(){
	return _infected;
}

cocos2d::Rect Human::getBoundingBox(){
	_sprite->getBoundingBox();
}

cocos2d::Point Human::wander(){
	cocos2d::Point pos 	  =	_sprite->getPosition(),
				   diff;
	int 		   diffX  = rand() % 3 - 1,
				   diffY  = rand() % 3 - 1;

	diff = cocos2d::ccp(diffX*16, diffY*16);
	//diff = cocos2d::ccp(16, 16);
	pos = cocos2d::ccpSub(pos, diff);

	return pos;
}

cocos2d::Point Human::moveFrom(cocos2d::Point target){
	cocos2d::Point pos = _sprite->getPosition(),
				   newPos;

	newPos = cocos2d::ccpSub(pos, target);
	if(newPos.x > 16)
		newPos = cocos2d::ccp(16, newPos.y);
	if(newPos.y > 16)
		newPos = cocos2d::ccp(newPos.x, 16);
	if(newPos.x < -16)
		newPos = cocos2d::ccp(-16, newPos.y);
	if(newPos.y < -16)
		newPos = cocos2d::ccp(newPos.x, -16);
	newPos = cocos2d::ccpAdd(pos, newPos);

	return newPos;
}

cocos2d::Point Human::moveToward(cocos2d::Point target){
	cocos2d::Point pos = _sprite->getPosition(),
				   newPos;

	newPos = cocos2d::ccpSub(pos, target);
	if(newPos.x > 16)
		newPos = cocos2d::ccp(16, newPos.y);
	if(newPos.y > 16)
		newPos = cocos2d::ccp(newPos.x, 16);
	if(newPos.x < -16)
		newPos = cocos2d::ccp(-16, newPos.y);
	if(newPos.y < -16)
		newPos = cocos2d::ccp(newPos.x, -16);
	newPos = cocos2d::ccpSub(pos, newPos);

	return newPos;
}

// implement UDLR
cocos2d::Point Human::moveLeft(){
	cocos2d::Point pos = _sprite->getPosition();

	pos = cocos2d::ccpSub(pos, cocos2d::ccp(16,0));

	return pos;
}
cocos2d::Point Human::moveRight(){
	cocos2d::Point pos = _sprite->getPosition();

	pos = cocos2d::ccpAdd(pos, cocos2d::ccp(16,0));

	return pos;
}
cocos2d::Point Human::moveUp(){
	cocos2d::Point pos = _sprite->getPosition();

	pos = cocos2d::ccpAdd(pos, cocos2d::ccp(0,16));

	return pos;
}

cocos2d::Point Human::moveDown(){
	cocos2d::Point pos = _sprite->getPosition();

	pos = cocos2d::ccpSub(pos, cocos2d::ccp(0,16));

	return pos;
}

bool Human::collidesWithSprite(cocos2d::Sprite *target){
	//where targetSpriteArray is CCArray which contains your target sprites and bulletSprite is the sprite of your bullet
	cocos2d::Rect targetRect = target->boundingBox();
	cocos2d::Rect humanRect = _sprite->boundingBox();
	if(humanRect.intersectsRect(targetRect))
	{
		// collided
		return true;
	}
	return false;
}
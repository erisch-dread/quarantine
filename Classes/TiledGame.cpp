#include "TiledGame.h"


TiledGame::TiledGame(std::string path, cocos2d::Layer *layer){
	_parent = layer;

	_tileMap = cocos2d::TMXTiledMap::create(path);

	_meta = _tileMap->layerNamed("meta");
	_meta->setVisible(false);

	_parent->addChild(_tileMap);
}

cocos2d::TMXObjectGroup *TiledGame::getObjects(){
	cocos2d::TMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
	return objectGroup;
}

cocos2d::TMXLayer *TiledGame::getMetaLayer(){
	return _meta;
}

cocos2d::Point TiledGame::tileCoordAt(cocos2d::Point pos){
	int x = pos.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;

    cocos2d::Point newPoint = cocos2d::Point((float)x, (float)y);

    return newPoint;
}

void TiledGame::setViewPointCenter(cocos2d::Point newCenter){
	cocos2d::Size winSize = cocos2d::Director::sharedDirector()->getWinSize();
 
    int x = MAX(newCenter.x, winSize.width/2);
    int y = MAX(newCenter.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    cocos2d::Point actualPosition = cocos2d::ccp(x, y);
 
    cocos2d::Point centerOfView = cocos2d::ccp(winSize.width/2, winSize.height/2);
    cocos2d::Point viewPoint = cocos2d::ccpSub(centerOfView, actualPosition);
    _parent->setPosition(viewPoint);
}

bool TiledGame::collidable(cocos2d::Point tileCoord){
    tileCoord = tileCoordAt(tileCoord);
    unsigned int gid = _meta->getTileGIDAt(tileCoord);
    if(gid) {
        cocos2d::ValueMap properties = _tileMap->getPropertiesForGID(gid).asValueMap();

        if(!properties.empty()) {
            auto collision = properties["Collidable"].asString();

            if("True" == collision) {
                return true;
            }
        }
    }

    return false;
}
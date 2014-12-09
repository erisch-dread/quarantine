#ifndef __TILEDGAME_H__
#define __TILEDGAME_H__

#include "cocos2d.h"
#include <string>

class TiledGame
{
	private:
		cocos2d::Layer 			*_parent;
		cocos2d::TMXTiledMap	*_tileMap;
		cocos2d::TMXLayer		*_meta;

	public:
		//CONSTRUCTOR -- loads tilemap, sets meta layer not visible
		TiledGame(std::string path, cocos2d::Layer *layer);

		//Tile Methods
		bool					tileIsCollidableAt(cocos2d::Point);
		bool					collidable(cocos2d::Point);
		void 					setViewPointCenter(cocos2d::Point newCenter);
		cocos2d::Point 			tileCoordAt(cocos2d::Point pos);
		
		//Objects (like SpawnPoints)
		cocos2d::TMXObjectGroup	*getObjects();

		cocos2d::TMXLayer		*getMetaLayer();
};

		

#endif // __TILEDGAME_H__
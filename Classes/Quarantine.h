#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "TiledGame.h"
#include "Human.h"

#define UPDATE_DELTA 	0.1
#define HUMAN_NUM	 	100
#define HUMAN_VIEW_RAD	128
#define SPRITE_SIZE		16

class Quarantine : public cocos2d::Layer
{
	private:
		TiledGame 				*_world;
		Human					*_human;
		//Human 					*_infected;
		Human 					*_humans[HUMAN_NUM];
		cocos2d::TMXLayer		*_meta;
		cocos2d::TMXObjectGroup	*_objectGroup;
		float 					updateDelta;

	public:
		CREATE_FUNC(Quarantine);
	    
	    static cocos2d::Scene*	createScene();
	    virtual bool 			init();  
	    void 					menuCloseCallback(cocos2d::Ref* pSender);
	    void 					update(float) override;

		//My stuff down here------------------------
		void 					setViewpointCenter(cocos2d::Point pos);
		cocos2d::Point 			tileCoordAt(cocos2d::Point pos);

		void					moveHuman(Human **man);
		void 					moveHuman(Human *man, Human *otherMan);
		bool					manOnManCollision(cocos2d::Point pos, Human **man, int index);

		cocos2d::Point			getZombieAvgPos();
		cocos2d::Point			getNearestHumanPos(cocos2d::Point source);
		cocos2d::Point			getNearestZombiePos(cocos2d::Point origin);
};

#endif // __HELLOWORLD_SCENE_H__

#include "Quarantine.h"

cocos2d::Scene* Quarantine::createScene()
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Quarantine::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Quarantine::init()
{
    //Make sure loading didn't fail.
    if ( !Layer::init() )
        return false;
    
    //Load the tilemap...
    _world = new TiledGame("tilemaps/test_map.tmx", this);
   
    //Load the character(s)...
    int x = _world->getObjects()->objectNamed("SpawnPoint").at("x").asInt();
    int y = _world->getObjects()->objectNamed("SpawnPoint").at("y").asInt();

    //Load the character(s)
    for(int i=0; i<HUMAN_NUM; i++){
        int a = std::rand() % 800;
        int b = std::rand() % 800;
        cocos2d::Point spawnPoint = cocos2d::ccp(a,b);
        
        while (_world->collidable(spawnPoint)){
            a = std::rand() % 800;
            b = std::rand() % 800;
            spawnPoint = cocos2d::ccp(a,b);
        }


        _humans[i] = new Human("sprites/jigglybit.png", cocos2d::ccp(a,b), this);
    }
    _humans[0]->infect();
    
    //_human = new Human("sprites/jigglybit.png", cocos2d::ccp(x,y), this);
    //infected with COOTIES! they wanna touch someone who doesn't have cooties for some reason
    //_infected = new Human("sprites/jigglybit.png", cocos2d::ccp(x+300, y-200), this);
    //_infected->infect();

    //Initialize main app vars
    updateDelta = 0;

    //Start the game loop
    this->scheduleUpdate();
    
    return true;
}

void Quarantine::update(float delta){
    updateDelta += delta;

    if(updateDelta >= UPDATE_DELTA){
        moveHuman(_humans);
        //moveHuman(_infected, _human);

        updateDelta = 0;
    }
}

void Quarantine::moveHuman(Human **man){

    for(int i=0; i<HUMAN_NUM; i++){
        cocos2d::Point zombiesPos = getNearestZombiePos(man[i]->getPosition());
        cocos2d::Point pos;
        if(!man[i]->isInfected()){
            //cocos2d::Point zombiesPos = getNearestZombiePos(man[i]->getPosition());
            //if(!(*zombieDist < 64))
            //if !getdistance
            if()
            pos = man[i]->moveFrom(zombiesPos);
        }
        else {
            pos = man[i]->moveToward(getNearestHumanPos(man[i]->getPosition()));
        }
        if(!_world->collidable(pos)){
            man[i]->setPosition(pos);
        }
        else {
            if(pos.x < man[i]->getPosition().x) {
                cocos2d::Point tryLeft = man[i]->moveLeft();
                if(!_world->collidable(tryLeft)){
                    man[i]->setPosition(tryLeft);
                }
            }
            if(pos.x > man[i]->getPosition().x){
                cocos2d::Point tryRight = man[i]->moveRight();
                if(!_world->collidable(tryRight)){
                    man[i]->setPosition(tryRight);
                }
            }
            if(pos.y < man[i]->getPosition().y){
                cocos2d::Point tryDown = man[i]->moveDown();
                if(!_world->collidable(tryDown)){
                    man[i]->setPosition(tryDown);
                }
            }
            if(pos.y > man[i]->getPosition().y){
                cocos2d::Point tryUp = man[i]->moveUp();
                if(!_world->collidable(tryUp)) {
                    man[i]->setPosition(tryUp);
                }
            }   
        } 
    }
}

void Quarantine::moveHuman(Human *man, Human *otherMan){
    cocos2d::Point pos;  
    if(!man->isInfected())
        pos = man->moveFrom(otherMan->getPosition());
    else
        pos = man->moveToward(otherMan->getPosition());     

    if(!_world->collidable(pos)){
        man->setPosition(pos);
    }
    else {
        if(pos.x < man->getPosition().x) {
            cocos2d::Point tryLeft = man->moveLeft();
            if(!_world->collidable(tryLeft))
                man->setPosition(tryLeft);
        }
        else if(pos.x > man->getPosition().x){
            cocos2d::Point tryRight = man->moveRight();
            if(!_world->collidable(tryRight))
                man->setPosition(tryRight);
        }
        else if(pos.y < man->getPosition().y){
            cocos2d::Point tryUp = man->moveUp();
            if(!_world->collidable(tryUp))
                man->setPosition(tryUp);
        }
        else if(pos.y > man->getPosition().y){
            cocos2d::Point tryDown = man->moveDown();
            if(!_world->collidable(tryDown))
                man->setPosition(tryDown);
        }   
    } 
}

cocos2d::Point Quarantine::getZombieAvgPos(){
    cocos2d::Point avgPos = cocos2d::Point(0,0);
    int            zombieCount = 0;

    for(int i=0; i<HUMAN_NUM; i++){
        if(_humans[i]->isInfected()){
            cocos2d::Point infectedPos = _humans[i]->getPosition();
            avgPos = cocos2d::ccpAdd(avgPos, infectedPos);
            ++zombieCount;
        }
    }

    avgPos = cocos2d::ccpMult(avgPos, 1.0f/(float)zombieCount);
    cocos2d::Point test = _humans[0]->getPosition();

    return avgPos;
}

cocos2d::Point Quarantine::getNearestHumanPos(cocos2d::Point source){
    float closestDistance = -1;
    Human *closestHuman;

    for(int i=0; i<HUMAN_NUM; i++){
        if(!_humans[i]->isInfected()){
            cocos2d::Point infectedPos = _humans[i]->getPosition();
            cocos2d::Point distToInfected = cocos2d::ccpSub(source, infectedPos);
            distToInfected = cocos2d::ccp(std::pow(distToInfected.x, 2), std::pow(distToInfected.y, 2));
            float distance = std::sqrt(distToInfected.x + distToInfected.y);
            if(closestDistance == -1 || distance < closestDistance){
                closestHuman = _humans[i];
                closestDistance = distance;
            }

        }
    }

    if(closestDistance < 16){
        closestHuman->infect();
    }
    //avgPos = cocos2d::ccpMult(avgPos, 1.0f/(float)HUMAN_NUM);
    //cocos2d::Point test = _humans[0]->getPosition();

    return closestHuman->getPosition();
}

cocos2d::Point Quarantine::getNearestZombiePos(cocos2d::Point source){
    float closestDistance = -1;
    Human *closestHuman;

    for(int i=0; i<HUMAN_NUM; i++){
        if(_humans[i]->isInfected()){
            cocos2d::Point infectedPos = _humans[i]->getPosition();
            cocos2d::Point distToInfected = cocos2d::ccpSub(source, infectedPos);
            distToInfected = cocos2d::ccp(std::pow(distToInfected.x, 2), std::pow(distToInfected.y, 2));
            float distance = std::sqrt(distToInfected.x + distToInfected.y);

            if(closestDistance == -1 || distance < closestDistance){
                closestHuman = _humans[i];
                closestDistance = distance;
            }
        }
    }

    cocos2d::Point closestPoint = closestHuman->getPosition();

    //if(closestDistance < 64){
    //    closestPoint = closestHuman->getPosition();
    //}
    //avgPos = cocos2d::ccpMult(avgPos, 1.0f/(float)HUMAN_NUM);
    //cocos2d::Point test = _humans[0]->getPosition();

    return closestPoint;
}

void Quarantine::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

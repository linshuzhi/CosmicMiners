//
//  LandLayer.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#include "LandLayer.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/ItemManager.h"
#include "LandSprite.h"
#include "WallSprite.h"
#include "HeroSprite.h"
#include "DiamondRedSprite.h"
#include "DiamondBlueSprite.h"
#include "DoorSprite.h"
#include "BallSprite.h"
#include "ItemSpriteBase.h"
#include "DevilSprite.h"
USING_NS_CC;
LandLayer::LandLayer(){
    
}
LandLayer::~LandLayer(){
    
}
bool LandLayer::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const std::vector<cocos2d::Point>& wallPoints = GameManager::getInstance()->getWallPoints();
    const std::vector<cocos2d::Point>& landPoints = GameManager::getInstance()->getLandPoints();
    
    const std::vector<cocos2d::Point>& redPoints = GameManager::getInstance()->getDiamondsRedPoints();
    const std::vector<cocos2d::Point>& bluePoints = GameManager::getInstance()->getDiamondsBluePoints();
    const std::vector<cocos2d::Point>& ballPoints = GameManager::getInstance()->getBallPoints();

    //land
    for (auto landpoint : landPoints) {
        Point point = GameManager::getInstance()->getRealPoint(landpoint);
        auto land = LandSprite::create();
        land->setIndexPoint(landpoint);
        land->setPosition( point);
        addChild(land);
    }
    //wall
    for (auto wallpoint : wallPoints) {
        Point point = GameManager::getInstance()->getRealPoint(wallpoint);
        auto wall = WallSprite::create();
        wall->setIndexPoint(wallpoint);
        wall->setPosition( point);
        addChild(wall);
    }
    //red diamond
    for (auto redpoint : redPoints) {
        Point point = GameManager::getInstance()->getRealPoint(redpoint);
        auto red = DiamondRedSprite::create();
        red->setIndexPoint(redpoint);
        red->setPosition( point);
        addChild(red);
    }
    // blue diamond
    for (auto bluepoint : bluePoints) {
        Point point = GameManager::getInstance()->getRealPoint(bluepoint);
        auto blue = DiamondBlueSprite::create();
        blue->setIndexPoint(bluepoint);
        blue->setPosition( point);
        addChild(blue);
    }
    
    // ball
    for (auto ballpoint : ballPoints) {
        Point point = GameManager::getInstance()->getRealPoint(ballpoint);
        auto ball = BallSprite::create();
        ball->setIndexPoint(ballpoint);
        ball->setPosition( point);
        addChild(ball);
    }
    
    
    //hero
    cocos2d::Point heroIndexPoint = GameManager::getInstance()->getHeroPoints();
    cocos2d::Point heroPoint = GameManager::getInstance()->getRealPoint(heroIndexPoint);
    auto hero = HeroSprite::create();
    hero->setIndexPoint(heroIndexPoint);
    hero->setPosition( heroPoint);
    addChild(hero);
    
    //door
    cocos2d::Point doorIndexPoint = GameManager::getInstance()->getDoorPoints();
    cocos2d::Point doorPoint = GameManager::getInstance()->getRealPoint(doorIndexPoint);
    auto door = DoorSprite::create();
    door->setIndexPoint(doorIndexPoint);
    door->setPosition( doorPoint);
    addChild(door);
    //devil
    const std::vector<cocos2d::Point>& devilPoints = GameManager::getInstance()->getDevilPoints();
    for (auto devilpoint : devilPoints) {
        Point point = GameManager::getInstance()->getRealPoint(devilpoint);
        auto devil = DevilSprite::create();
        devil->setIndexPoint(devilpoint);
        devil->setPosition( point);
        addChild(devil);
    }
    
    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LandLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    setAnchorPoint(Point(0,0.5f));
    setScale(visibleSize.width / visibleSize.height);//
    return true;
}

bool LandLayer::onContactBegin(PhysicsContact& contact){
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    ItemManager::getInstance()->onContact(
        dynamic_cast<ItemSpriteBase*>(nodeA), dynamic_cast<ItemSpriteBase*>(nodeB));

    return true;
}




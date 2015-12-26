//
//  HeroSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/20.
//
//

#include "HeroSprite.h"
#include "../../Manager/TouchManager.h"
#include "../../Manager/ItemManager.h"
#include "PhysicsBodyMask.h"
USING_NS_CC;

namespace  {
    const char* kFileName = "game/hero.png";
}




HeroSprite::HeroSprite()
: _isRunning(false)
, _dir(TouchManagerDelegate::direction_none)
{
    TouchManager::addDelegate(this);
}

HeroSprite::~HeroSprite(){
    TouchManager::deleteDelegate(this);
}
HeroSprite* HeroSprite::create(){
    
    HeroSprite *sprite = new (std::nothrow) HeroSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();
        auto body = PhysicsBody::createBox(sprite->getContentSize());
        body->setCategoryBitmask(MASK_HERO);
        body->setContactTestBitmask( MASK_BALL);
        body->setCollisionBitmask(0);
        sprite->setPhysicsBody(body);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
    
}

void HeroSprite::onTouchChange(TouchManagerDelegate::direction dir){
    _dir = dir;
    toNext();
    
}

void HeroSprite::toNext(){
    if (_isRunning) {
        return;
    }
    ItemManager::getInstance()->heroTryToNext(_dir, this);
}


void HeroSprite::runToPoint(cocos2d::Point point){
    _isRunning = true;
    auto move = MoveBy::create(0.1f, point - this->getPosition());
    auto act = Sequence::create(move,
                                CallFuncN::create([this](Node* node){
        this->_isRunning = false;
        this->toNext();
    }),
                                nullptr
                                );
    
    this->runAction(act);
}
void HeroSprite::slowToPoint(cocos2d::Point point){
    _isRunning = true;
    auto move = MoveBy::create(0.3f, point - this->getPosition());
    auto act = Sequence::create(move,
                                CallFuncN::create([this](Node* node){
        this->_isRunning = false;
        this->toNext();
    }),
                                nullptr
                                );
    
    this->runAction(act);
}



//
//  DropSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/23.
//
//

#include "DropSprite.h"
#include "../../Manager/ItemManager.h"
#include "PhysicsBodyMask.h"
USING_NS_CC;
DropSprite::DropSprite()
: _isMove(false)
, _moveTime(0)
{
    
}

DropSprite::~DropSprite(){
    
}

void DropSprite::scheduleSelf(){
    this->schedule(schedule_selector(DropSprite::onSch), 0.1f);
}
void DropSprite::onScheduleSelf(){
    
    if(_isMove){
        return ;
    }
    ItemManager::getInstance()->ItemTryToStartDrop(this);
}

void DropSprite::onSch(float f){
    onScheduleSelf();
}

void DropSprite::toNext(){
    if(_isMove){
        return ;
    }
    ItemManager::getInstance()->ItemTryToDrop(this);
}

void DropSprite::startToPoint(cocos2d::Point point){
    _isMove = true;
    _moveTime = 0.2f;
    auto move = MoveTo::create(_moveTime, point );
    auto act = Sequence::create(//DelayTime::create(0.1f),
                                move,
                                CallFuncN::create([this](Node* node){
        this->_isMove = false;
        //this->onScheduleSelf();
        this->toNext();
    }),
                                nullptr
                                );
    
    this->runAction(act);
}
void DropSprite::runToPoint(cocos2d::Point point){
    _isMove = true;
    _moveTime -= 0.04;
    _moveTime = 0.1f > _moveTime ? 0.1f : _moveTime;

    auto move = MoveTo::create(_moveTime, point);
    auto act = Sequence::create(
                                move,
                                CallFuncN::create([this](Node* node){
        this->_isMove = false;
        //this->onScheduleSelf();
        this->toNext();
    }),
                                nullptr
                                );
    
    this->runAction(act);
}


bool DropSprite::initWithFile(const std::string& filename){
    bool bRet = ItemSpriteBase::initWithFile(filename);
    scheduleSelf();
    
    auto body = PhysicsBody::createBox(Size(this->getContentSize().width - 2,this->getContentSize().height - 2));
    body->setCategoryBitmask(MASK_BALL);
    body->setContactTestBitmask(MASK_HERO);
    body->setCollisionBitmask(0);
    setPhysicsBody(body);
    return bRet;
}

bool DropSprite::isMoveing(){
    return _isMove;
}


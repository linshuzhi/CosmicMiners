//
//  BallSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/23.
//
//

#include "BallSprite.h"


#include "../../Manager/ItemManager.h"
#include "PhysicsBodyMask.h"
USING_NS_CC;

namespace  {
    const char* kFileName = "game/ball.png";
}
BallSprite::BallSprite(){
    
}
BallSprite::~BallSprite(){
    
}
BallSprite* BallSprite::create(){
    
    BallSprite *sprite = new (std::nothrow) BallSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();

        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
    
}

void BallSprite::slowToPoint(cocos2d::Point point){
    _isMove = true;
    auto move = MoveTo::create(0.3f, point);
    auto act = Sequence::create(move,
                                CallFuncN::create([this](Node* node){
        this->_isMove = false;
        this->toNext();
    }),
                                nullptr
                                );
    
    this->runAction(act);
}




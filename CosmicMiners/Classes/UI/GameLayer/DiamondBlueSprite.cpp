//
//  DiamondBlue.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/21.
//
//

#include "DiamondBlueSprite.h"
#include "../../Manager/ItemManager.h"
USING_NS_CC;

namespace  {
    const char* kFileName = "game/diamonds_blue.png";
    const int kScore = 1;
}
DiamondBlueSprite::DiamondBlueSprite(){
}
DiamondBlueSprite::~DiamondBlueSprite(){
    
}
DiamondBlueSprite* DiamondBlueSprite::create(){
    
    DiamondBlueSprite *sprite = new (std::nothrow) DiamondBlueSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    
    return nullptr;
    
}

int DiamondBlueSprite::getScore(){
    return kScore;
}









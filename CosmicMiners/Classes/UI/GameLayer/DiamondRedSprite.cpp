//
//  DiamondRed.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/21.
//
//

#include "DiamondRedSprite.h"
USING_NS_CC;


namespace  {
    const char* kFileName = "game/diamonds_red.png";
    const int kScore = 2;
}

DiamondRedSprite::DiamondRedSprite(){
    
}
DiamondRedSprite::~DiamondRedSprite(){
    
}
DiamondRedSprite* DiamondRedSprite::create(){
    
    DiamondRedSprite *sprite = new (std::nothrow) DiamondRedSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
    
}

int DiamondRedSprite::getScore(){
    return kScore;
}





//
//  DevilSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/25.
//
//

#include "DevilSprite.h"


namespace  {
    const char* kFileName = "game/devil.png";
}
DevilSprite* DevilSprite::create(){
    
    DevilSprite *sprite = new (std::nothrow) DevilSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
    
}

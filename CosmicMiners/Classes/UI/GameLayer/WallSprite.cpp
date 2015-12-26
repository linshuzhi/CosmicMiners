//
//  WallSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#include "WallSprite.h"


namespace  {
    const char* kFileName = "game/wall.png";
}
WallSprite* WallSprite::create(){
    
    WallSprite *sprite = new (std::nothrow) WallSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
    
}

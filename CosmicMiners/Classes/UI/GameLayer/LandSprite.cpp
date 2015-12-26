//
//  LandSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#include "LandSprite.h"

namespace  {
    const char* kFileName = "game/land.png";
}
LandSprite* LandSprite::create(){

    LandSprite *sprite = new (std::nothrow) LandSprite();
    if (sprite && sprite->initWithFile(kFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;

}

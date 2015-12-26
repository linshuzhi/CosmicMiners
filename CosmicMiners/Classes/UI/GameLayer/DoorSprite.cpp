//
//  DoorSprite.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/21.
//
//

#include "DoorSprite.h"

namespace  {
    const char* kFileNameGray = "game/door_gray.png";
    const char* kFileName = "game/door.png";
}
    

DoorSprite* DoorSprite::create(){
    DoorSprite *sprite = new (std::nothrow) DoorSprite();
    if (sprite && sprite->initWithFile(kFileNameGray))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


DoorSprite::DoorSprite()
: _isValid(false)
{
    
}
DoorSprite::~DoorSprite(){
    
}



void DoorSprite::lightenDoor(){
    this->setTexture(kFileName);
    _isValid = true;
}
bool DoorSprite::isValid(){
    return _isValid;
}


bool _isValid;
//
//  WallSprite.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#ifndef WallSprite_h
#define WallSprite_h

#include "cocos2d.h"
#include "ItemSpriteBase.h"
class WallSprite : public ItemSpriteBase{
public:
    static WallSprite* create();
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_wall;
    }
};

#endif /* WallSprite_h */

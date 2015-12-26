//
//  DevilSprite.h

//  CosmicMiners
//
//  Created by LinShulong on 15/12/25.
//
//

#ifndef DevilSprite_h
#define DevilSprite_h

#include "cocos2d.h"
#include "ItemSpriteBase.h"
class DevilSprite : public ItemSpriteBase{
public:
    static DevilSprite* create();
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_devil;
    }
};


#endif /* DevilSprite_h */

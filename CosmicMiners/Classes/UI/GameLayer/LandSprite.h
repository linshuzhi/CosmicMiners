//
//  LandSprite.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#ifndef LandSprite_h
#define LandSprite_h
#include "cocos2d.h"
#include "ItemSpriteBase.h"
class LandSprite : public ItemSpriteBase{
public:
    static LandSprite* create();
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_land;
    }
};
#endif /* LandSprite_h */

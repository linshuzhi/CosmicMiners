//
//  DiamondBlue.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/21.
//
//

#ifndef DiamondBlue_h
#define DiamondBlue_h
#include "cocos2d.h"
#include "DropSprite.h"

class DiamondBlueSprite : public DropSprite{
public:
    DiamondBlueSprite();
    ~DiamondBlueSprite();
    static int getScore();
    static DiamondBlueSprite* create();


    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_diamonds_blue;
    }
private:
    bool _isMove;
};
#endif /* DiamondBlue_h */

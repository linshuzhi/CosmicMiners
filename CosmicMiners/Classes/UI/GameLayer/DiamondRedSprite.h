//
//  DiamondRedSprite.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/21.
//
//

#ifndef DiamondRed_h
#define DiamondRed_h

#include "cocos2d.h"
#include "DropSprite.h"
class DiamondRedSprite : public DropSprite{
public:
    DiamondRedSprite();
    ~DiamondRedSprite();
    static int getScore();
    static DiamondRedSprite* create();
    
    
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_diamonds_red;
    }
private:
    bool _isMove;

};

#endif /* DiamondRed_h
*/

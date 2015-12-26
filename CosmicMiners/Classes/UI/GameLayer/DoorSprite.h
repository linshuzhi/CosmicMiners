//
//  DoorSprite.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/21.
//
//

#ifndef DoorSprite_h
#define DoorSprite_h
#include "cocos2d.h"
#include "ItemSpriteBase.h"
class DoorSprite : public ItemSpriteBase{
public:
    DoorSprite();
    ~DoorSprite();
    static DoorSprite* create();
    
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_door;
    }

    void lightenDoor();
    bool isValid();
protected:
    
    bool _isValid;
};

#endif /* DoorSprite_h */

//
//  BallSprite.hpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/23.
//
//

#ifndef BallSprite_h
#define BallSprite_h

#include "DropSprite.h"
#include "ItemSpriteBase.h"
class BallSprite : public DropSprite{
public:
    BallSprite();
    ~BallSprite();
    static BallSprite* create();
    
    void slowToPoint(cocos2d::Point point);
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_ball;
    }
private:
    
};
#endif /* BallSprite_h */

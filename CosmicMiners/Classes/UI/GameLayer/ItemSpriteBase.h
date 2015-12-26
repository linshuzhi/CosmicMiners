//
//  ItemSpriteBase.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/23.
//
//

#ifndef ItemSpriteBase_h
#define ItemSpriteBase_h
#include "cocos2d.h"
class ItemSpriteBase : public cocos2d::Sprite {
    
public:
    enum item_type{
        item_type_none = 0,
        item_type_land,
        item_type_wall,
        item_type_door,
        item_type_hero,
        item_type_diamonds_red,
        item_type_diamonds_blue,
        item_type_devil,
        item_type_ball,
    };
    
public:
    void setIndexPoint(cocos2d::Point point){
        _indexPoint = point;
    }
    
    cocos2d::Point getIndexPoint(){
        return _indexPoint;
    }
    ItemSpriteBase();
    ~ItemSpriteBase();
    virtual item_type getItemType() = 0;
    
    
private:
    cocos2d::Point _indexPoint;
    
    
};

#endif /* ItemSpriteBase_h */

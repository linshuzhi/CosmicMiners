//
//  HeroSprite.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/20.
//
//

#ifndef HeroSprite_h
#define HeroSprite_h

#include "cocos2d.h"
#include "ItemSpriteBase.h"
#include "../../Manager/TouchManagerDelegate.h"
class HeroSprite : public ItemSpriteBase, public TouchManagerDelegate{
public:
    HeroSprite();
    ~HeroSprite();
    static HeroSprite* create();
    
    void runToPoint(cocos2d::Point point);
    void slowToPoint(cocos2d::Point point);
    virtual void onTouchChange(TouchManagerDelegate::direction dir);
    virtual ItemSpriteBase::item_type getItemType(){
        return ItemSpriteBase::item_type_hero;
    }

protected:
    void toNext();
protected:
    TouchManagerDelegate::direction _dir;
    bool _isRunning;
};

#endif /* HeroSprite_h */

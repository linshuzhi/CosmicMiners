//
//  DropSprite.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/23.
//
//

#ifndef DropSprite_h
#define DropSprite_h


#include "ItemSpriteBase.h"
class DropSprite : public ItemSpriteBase {
    
public:
    DropSprite();
    ~DropSprite();
    void scheduleSelf();
    void onScheduleSelf();
    void onSch(float f);
    void runToPoint(cocos2d::Point point);
    void startToPoint(cocos2d::Point point);
    void toNext();
    virtual bool initWithFile(const std::string& filename);
    bool isMoveing();
protected:
    bool _isMove;
    float _moveTime;
    
};
#endif /* DropSprite_h */

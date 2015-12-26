//
//  LandLayer.hpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#ifndef LandLayer_h
#define LandLayer_h

#include "cocos2d.h"


class LandLayer : public cocos2d::Layer
{
public:
    LandLayer();
    ~LandLayer();
    virtual bool init();
    CREATE_FUNC(LandLayer);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
private:

private:

};

#endif /* LandLayer_h */

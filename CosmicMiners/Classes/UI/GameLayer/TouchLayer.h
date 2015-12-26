//
//  TouchLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#ifndef __RunRound__TouchLayer__
#define __RunRound__TouchLayer__

#include "cocos2d.h"
#include "../../Manager/TouchManagerDelegate.h"

class TouchLayerDelegate;
class TouchLayer : public cocos2d::Layer ,public TouchManagerDelegate
{
public:
    TouchLayer();
    ~TouchLayer();
    virtual bool init();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchChange(TouchManagerDelegate::direction dir);
    // implement the "static create()" method manually
    CREATE_FUNC(TouchLayer);
    void setDelegate(TouchLayerDelegate* delegate);
private:
    bool isOnTouch(cocos2d::Point point);
    void toTouchChange(TouchManagerDelegate::direction dir);
    TouchManagerDelegate::direction getDirection(cocos2d::Point point);
private:
    TouchLayerDelegate* _delegate;
    cocos2d::Sprite* _control;
    cocos2d::Sprite* _control_h;
    TouchManagerDelegate::direction _dir;
};

#endif /* defined(__RunRound__TouchLayer__) */

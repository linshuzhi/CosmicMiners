//
//  TouchLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "TouchLayer.h"
#include "../../Manager/TouchManager.h"
USING_NS_CC;


namespace  {
    const char * kControl = "game/control.png";
    const char * kControlH = "game/control_h.png";
    
}

TouchLayer::TouchLayer()
:_delegate(nullptr)
,_control(nullptr)
,_control_h(nullptr)
,_dir(TouchManagerDelegate::direction_none)
{
    
}
TouchLayer::~TouchLayer(){
    TouchManager::deleteDelegate(this);
}

void TouchLayer::setDelegate(TouchLayerDelegate* delegate){
    _delegate = delegate;
}

bool TouchLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    

    _control = Sprite::create(kControl);
    _control->setPosition(origin.x + visibleSize.width / 2, origin.y + _control->getContentSize().height / 2);
    addChild(_control);
    
    _control_h = Sprite::create(kControlH);
    _control_h->setPosition(0 + _control->getContentSize().width / 2,_control->getContentSize().height / 2);
    _control_h->setAnchorPoint(Vec2(0,0.5f));
    _control->addChild(_control_h);
    
    _control_h->setVisible(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded,this);
    listener->onTouchCancelled = CC_CALLBACK_2(TouchLayer::onTouchCancelled,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    TouchManager::addDelegate(this);
    return true;
}



bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
    bool ret = true;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Point point = touch->getLocation();
    TouchManagerDelegate::direction dir = getDirection(point);
    toTouchChange(dir);
    if (dir == TouchManagerDelegate::direction_none) {
        ret = false;
    }
    
    return ret;
}
void TouchLayer::toTouchChange(TouchManagerDelegate::direction dir){
    if (_dir == dir) {
        return ;
    }
    _dir = dir;
    TouchManager::touchChange(dir);
}


void TouchLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
    Point point = touch->getLocation();
    toTouchChange(getDirection(point));
}

void TouchLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
    toTouchChange(TouchManagerDelegate::direction_none);
}

void TouchLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){
    toTouchChange(TouchManagerDelegate::direction_none);
}

bool TouchLayer::isOnTouch(cocos2d::Point point){
    auto cPoint = _control->getPosition();
    auto size = _control->getContentSize();
    if(point.x < cPoint.x - size.width / 2){
        return false;
    }
    if(point.x > cPoint.x + size.width / 2){
        return false;
    }
    if(point.y < cPoint.y - size.height / 2){
        return false;
    }
    if(point.y > cPoint.y + size.height / 2){
        return false;
    }
    return true;
}

TouchManagerDelegate::direction TouchLayer::getDirection(cocos2d::Point point){
    if (!isOnTouch(point)) {
        return TouchManagerDelegate::direction_none;
    }
    auto cPoint = _control->getPosition();
    int lx = point.x - cPoint.x;
    int ly = point.y - cPoint.y;
    if (lx > ly) {
        if(lx > -ly){
            return TouchManagerDelegate::direction_right;
        }else{
            return TouchManagerDelegate::direction_down;
        }
    }else{
        if(lx > -ly){
            return TouchManagerDelegate::direction_up;
        }else{
            return TouchManagerDelegate::direction_left;
        }
    }
    return TouchManagerDelegate::direction_none;
    
}

void TouchLayer::onTouchChange(TouchManagerDelegate::direction dir){
    switch (dir) {
        case TouchManagerDelegate::direction_left:
            _control_h->setVisible(true);
            _control_h->setRotation(180);
            break;
        case TouchManagerDelegate::direction_right:
            _control_h->setVisible(true);
            _control_h->setRotation(0);
            break;
        case TouchManagerDelegate::direction_up:
            _control_h->setVisible(true);
            _control_h->setRotation(270);
            break;
        case TouchManagerDelegate::direction_down:
            _control_h->setVisible(true);
            _control_h->setRotation(90);
            break;
        default:
            _control_h->setVisible(false);
            break;
    }
}



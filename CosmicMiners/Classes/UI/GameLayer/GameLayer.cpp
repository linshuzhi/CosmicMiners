//
//  GameLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "GameLayer.h"
#include "../../Manager/DirectorManager.h"
//#include "TouchLayer.h"
//#include "BallLayer.h"
//#include "BubbleLayer.h"
//#include "OriginLayer.h"
//#include "PhysicsBodyMask.h"
#include "WinLayer.h"
#include "LoseLayer.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/SoundManager.h"
#include "LandLayer.h"
#include "TouchLayer.h"
//#include "../AdsHelp.h"
USING_NS_CC;

namespace  {
    const char * kBg = "main/game.jpg";
    const char * kBack = "back.png";
    const int kTouch = 10;
//    const char * kButtonOgg = "sound/button.m4a";
//    const char * kNextOgg = "sound/next.m4a";
//    const char * kRunOgg = "sound/run.m4a";
//    
//    const char * kPileOgg = "sound/pile.m4a";
//    const char * kVictoryOgg = "sound/victory.m4a";
//    const char * kFailureOgg = "sound/failure.m4a";
//    const char * kRunBgOgg = "sound/run_bg.m4a";
//    const char * kBoomOgg = "sound/boom.m4a";
    
    
}

GameLayer::GameLayer()
: _balllayer(nullptr)
, _originLayer(nullptr)
, _disBubble(0)
, _pileCount(0)
, _touchLayer(nullptr)
, _bTouch(true)
{
    
}
GameLayer::~GameLayer(){
    SoundManager::stopBackgroundMusic();
}
bool GameLayer::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto landLayer = LandLayer::create();
    addChild(landLayer);
    auto touchLayer = TouchLayer::create();
    addChild(touchLayer,kTouch);
    
    GameManager::getInstance()->setGameLayer(this);
    return true;
}

bool GameLayer::onContactBegin(PhysicsContact& contact)
{
        return true;
}

void GameLayer::disBubble(cocos2d::Node* node){

}

void GameLayer::showWinLayer(){
    auto layer = WinLayer::create();
    addChild(layer,kTouch);
}

void GameLayer::showLoseLayer(){
    auto layer = LoseLayer::create();
    addChild(layer,kTouch);
}


void GameLayer::addBallLayer(){

    
}

void GameLayer::addBubbleayer(){

    
    
}

void GameLayer::addOriginLayer(){

    
    
    
}





void GameLayer::menuCallback(cocos2d::Ref* pSender){
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_LEVEL);
}

void GameLayer::onTouchLayerButton(){


    
}

void GameLayer::onTouchLayerTouch(cocos2d::Point point){

    
}

void GameLayer::gameLose(){
    showLoseLayer();
}


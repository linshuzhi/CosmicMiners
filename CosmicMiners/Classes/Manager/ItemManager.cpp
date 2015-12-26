//
//  ItemManager.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/19.
//
//

#include "ItemManager.h"
#include "GameManager.h"
#include "../UI/GameLayer/ItemSpriteBase.h"
#include "../UI/GameLayer/HeroSprite.h"
#include "../UI/GameLayer/DiamondBlueSprite.h"
#include "../UI/GameLayer/DiamondRedSprite.h"
#include "../UI/GameLayer/DoorSprite.h"
#include "DirectorManager.h"
#include "../UI/GameLayer/BallSprite.h"


USING_NS_CC;
ItemManager* ItemManager::_instance = nullptr;
ItemManager::ItemManager(){
    
}
ItemManager::~ItemManager(){
    
}
ItemManager* ItemManager::getInstance(){
    if (!_instance) {
        _instance = new ItemManager();
        _instance->init();
    }
    return _instance;
}

void ItemManager::reset(){
    delete _instance;
    _instance = nullptr;
}
void ItemManager::init(){
    
}

void ItemManager::addItem(ItemSpriteBase* item){
    _items.push_back(item);
}

void ItemManager::deleteItem(ItemSpriteBase* item){
    for (std::vector<ItemSpriteBase*>::iterator iter = _items.begin(); iter != _items.end(); iter++) {
        if(*iter == item){
            _items.erase(iter);
            break;
        }
    }
}
cocos2d::Point ItemManager::getNextPoint(TouchManagerDelegate::direction dir,cocos2d::Point point){
    cocos2d::Point retP = point;
    switch (dir) {
        case TouchManagerDelegate::direction_left :
            retP.x--;
            break;
        case TouchManagerDelegate::direction_right :
            retP.x++;
            break;
        case TouchManagerDelegate::direction_up :
            retP.y++;
            break;
        case TouchManagerDelegate::direction_down :
            retP.y--;
            break;
        default:
            break;
    }
    return retP;
}
bool ItemManager::heroTryToNext(TouchManagerDelegate::direction dir,HeroSprite* hero){
    cocos2d::Point indexPoint = getNextPoint(dir,hero->getIndexPoint());
    bool bNull = true;
    for (auto item : _items) {
        if (item->getIndexPoint() == indexPoint) {
            bNull = false;
            if (item->getItemType() == ItemSpriteBase::item_type_land) {
                item->removeFromParent();
                deleteItem(item);
                hero->setIndexPoint(indexPoint);
                hero->runToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
                return true;
            }else if(item->getItemType() == ItemSpriteBase::item_type_diamonds_blue){
                item->removeFromParent();
                deleteItem(item);
                hero->setIndexPoint(indexPoint);
                hero->runToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
                GameManager::getInstance()->addScore(DiamondBlueSprite::getScore());
                return true;
            }else if(item->getItemType() == ItemSpriteBase::item_type_diamonds_red){
                item->removeFromParent();
                deleteItem(item);
                hero->setIndexPoint(indexPoint);
                hero->runToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
                GameManager::getInstance()->addScore(DiamondRedSprite::getScore());
                return true;
            }else if(item->getItemType() == ItemSpriteBase::item_type_door){
                if (dynamic_cast<DoorSprite*>(item)->isValid()) {
                    item->removeFromParent();
                    deleteItem(item);
                    hero->setIndexPoint(indexPoint);
                    hero->runToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
                    GameManager::getInstance()->setLevelSuccess();
                    GameManager::getInstance()->showWinLayer();
                }
                return true;
            }else if(item->getItemType() == ItemSpriteBase::item_type_ball){
                auto ball = dynamic_cast<BallSprite*>(item);
                if (!ball->isMoveing()) {
                    auto secondPoint = getNextPoint(dir,indexPoint);
                    if (!getItemByPoint(secondPoint)) {
                        //如果物品后面的不存在，则推动物品
                        
                        ball->setIndexPoint(secondPoint);
                        ball->slowToPoint(GameManager::getInstance()->getRealPoint(secondPoint));
                        hero->setIndexPoint(indexPoint);
                        hero->slowToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
                        
                    }
                }
                
                return true;
            }
            break;
        }
    }
    if (bNull) {
        hero->setIndexPoint(indexPoint);
        hero->runToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
    }
    return false;
}
bool ItemManager::ItemTryToStartDrop(DropSprite* drop){
    cocos2d::Point indexPoint = drop->getIndexPoint();
    indexPoint.y--;
    bool bNull = true;
    for (auto item : _items) {
        if (item->getIndexPoint() == indexPoint) {
            bNull = false;
            auto type_ = item->getItemType();
            if(type_ == ItemSpriteBase::item_type_ball ||
               type_ == ItemSpriteBase::item_type_diamonds_red ||
               type_ == ItemSpriteBase::item_type_diamonds_blue){
                auto left = Point(indexPoint.x - 1,indexPoint.y);
                if(!getItemByPoint(left) && !getItemByPoint(Point(left.x,left.y+1))){
                    drop->setIndexPoint(left);
                    drop->runToPoint(GameManager::getInstance()->getRealPoint(left));
                    return true;
                }
                auto right = Point(indexPoint.x + 1,indexPoint.y);
                if(!getItemByPoint(right) && !getItemByPoint(Point(right.x,right.y+1))){
                    drop->setIndexPoint(right);
                    drop->runToPoint(GameManager::getInstance()->getRealPoint(right));
                    return true;
                }
            }
            break;
        }
    }
    if (bNull) {
        drop->setIndexPoint(indexPoint);
        drop->startToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
    }
    return true;
}
bool ItemManager::ItemTryToDrop(DropSprite* drop){
    cocos2d::Point indexPoint = drop->getIndexPoint();
    indexPoint.y--;
    bool bNull = true;
    for (auto item : _items) {
        if (item->getIndexPoint() == indexPoint) {
            bNull = false;
            auto type_ = item->getItemType();
            if(type_ == ItemSpriteBase::item_type_ball ||
               type_ == ItemSpriteBase::item_type_diamonds_red ||
               type_ == ItemSpriteBase::item_type_diamonds_blue){
                auto left = Point(indexPoint.x - 1,indexPoint.y);
                if(!getItemByPoint(left) && !getItemByPoint(Point(left.x,left.y+1))){
                    drop->setIndexPoint(left);
                    drop->runToPoint(GameManager::getInstance()->getRealPoint(left));
                    return true;
                }
                auto right = Point(indexPoint.x + 1,indexPoint.y);
                if(!getItemByPoint(right) && !getItemByPoint(Point(right.x,right.y+1))){
                    drop->setIndexPoint(right);
                    drop->runToPoint(GameManager::getInstance()->getRealPoint(right));
                    return true;
                }
            }else if(isMobileType(item)){
                bNull = true;
            }
            break;
        }
    }
    if (bNull) {
        drop->setIndexPoint(indexPoint);
        drop->runToPoint(GameManager::getInstance()->getRealPoint(indexPoint));
    }
    return true;
}

bool ItemManager::isMobileType(ItemSpriteBase* item){
    auto type_ = item->getItemType();
    if (type_ == ItemSpriteBase::item_type_hero ||
        type_ == ItemSpriteBase::item_type_devil ) {
        return true;
    }
    return false;
}


ItemSpriteBase* ItemManager::getItemByPoint(cocos2d::Point point){
    for (auto item : _items) {
        if (item->getIndexPoint() == point){
            return item;
        }
    }
    return nullptr;
}

void ItemManager::lightenDoor(){
    for (auto item : _items) {
        if (item->getItemType() == ItemSpriteBase::item_type_door){
            dynamic_cast<DoorSprite*>(item)->lightenDoor();
            return ;
        }
    }

}

void ItemManager::onContact(ItemSpriteBase* itemA,ItemSpriteBase* itemB){
    if (checkHeroContact(itemA,itemB)) return;
    if (checkDevilContact(itemA,itemB)) return;
}

bool ItemManager::checkHeroContact(ItemSpriteBase* itemA,ItemSpriteBase* itemB){
    ItemSpriteBase* hero = nullptr;
    if (itemA->getItemType() == ItemSpriteBase::item_type_hero) {
        hero = itemA;
    }
    if (itemB->getItemType() == ItemSpriteBase::item_type_hero) {
        hero = itemB;
    }
    if (!hero) {
        return false;
    }
    hero->removeFromParent();
    GameManager::getInstance()->showLoseLayer();
    
    return true;
}

bool ItemManager::checkDevilContact(ItemSpriteBase* itemA,ItemSpriteBase* itemB){
    ItemSpriteBase* devil = nullptr;
    if (itemA->getItemType() == ItemSpriteBase::item_type_devil) {
        devil = itemA;
    }
    if (itemB->getItemType() == ItemSpriteBase::item_type_devil) {
        devil = itemB;
    }
    if (!devil) {
        return false;
    }
    
    
    return true;
}






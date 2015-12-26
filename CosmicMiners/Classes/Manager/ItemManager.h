//
//  ItemManager.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/19.
//
//

#ifndef ItemManager_h
#define ItemManager_h

#include "TouchManagerDelegate.h"

#include "cocos2d.h"
#include <vector>
class ItemSpriteBase;
class HeroSprite;
class DropSprite;
class ItemManager{
public:
    ItemManager();
    ~ItemManager();
    static ItemManager* getInstance();
public:
    void reset();
    void addItem(ItemSpriteBase* item);
    void deleteItem(ItemSpriteBase* item);
    bool heroTryToNext(TouchManagerDelegate::direction dir,HeroSprite* hero);
    bool ItemTryToDrop(DropSprite* drop);
    bool ItemTryToStartDrop(DropSprite* drop);
    cocos2d::Point getNextPoint(TouchManagerDelegate::direction dir,cocos2d::Point point);
    void lightenDoor();
    ItemSpriteBase* getItemByPoint(cocos2d::Point point);
    void onContact(ItemSpriteBase* itemA,ItemSpriteBase* itemB);
private:
    bool checkHeroContact(ItemSpriteBase* itemA,ItemSpriteBase* itemB);
    bool checkDevilContact(ItemSpriteBase* itemA,ItemSpriteBase* itemB);
    void init();
    bool isMobileType(ItemSpriteBase* item);                //是否是活动的
private:
    static ItemManager* _instance;
    std::vector<ItemSpriteBase* > _items;
};



#endif /* ItemManager_h */

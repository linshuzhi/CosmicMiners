//
//  ItemSpriteBase.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/23.
//
//

#include "ItemSpriteBase.h"
#include "../../Manager/ItemManager.h"

ItemSpriteBase::ItemSpriteBase()
: _indexPoint(0,0)
{
    ItemManager::getInstance()->addItem(this);
}
ItemSpriteBase::~ItemSpriteBase()
{
    ItemManager::getInstance()->deleteItem(this);
}
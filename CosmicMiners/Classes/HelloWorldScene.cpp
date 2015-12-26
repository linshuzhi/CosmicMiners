#include "HelloWorldScene.h"
#include "GameOverScene.h"
USING_NS_CC;

#define MOVE_SIZE		32
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
	_numCollected = 0;
    // 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	

	std::string file = "TiledMap.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	_tileMap = TMXTiledMap::createWithXML(str->getCString(), "");
	_background = _tileMap->layerNamed("Background");
	addChild(_tileMap, -1);

	TMXObjectGroup *objects = _tileMap->getObjectGroup("Obj");
	CCASSERT(NULL != objects, "'Objects' object group not found");
	auto spawnPoint = objects->getObject("SpawnPoint");
	CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	_player = Sprite::create("Player.png");
	_player->setPosition(x, y);
	addChild(_player);
	setViewPointCenter(_player->getPosition());




	auto listener = EventListenerTouchOneByOne::create();
	//lambda expression: advanced feature in C++ 11
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_meta = _tileMap->getLayer("meta");
	_meta->setVisible(false);
	_land = _tileMap->getLayer("Land");
	_Direction = MOVE_LEFT;
	animatePlayer(_player);


	for (auto& eSpawnPoint : objects->getObjects()) {
		ValueMap& dict = eSpawnPoint.asValueMap();
		if (dict["Enemy"].asInt() == 1) {
			x = dict["x"].asInt();
			y = dict["y"].asInt();
			this->addEnemyAtPos(Point(x, y));
		}
	}

	this->schedule(schedule_selector(HelloWorld::testCollisions));
    
    scheduleUpdate();
	return true;
}
void HelloWorld::update(float delta){
    //CCLOG("update");
    this->setViewPointCenter(_player->getPosition());
}
void HelloWorld::addEnemyAtPos(Point pos)
{
	auto enemy = Sprite::create("enemy1.png");
	enemy->setPosition(pos);
	this->addChild(enemy);
	enemy->setTag(MOVE_RIGHT);
	animateEnemy(enemy);
	_enemies.pushBack(enemy);
}

void HelloWorld::enemyMoveFinished(Object *pSender)
{
	Sprite *enemy = (Sprite *)pSender;

	this->animateEnemy(enemy);
}

void move_f(Move_Direction Direction, cocos2d::Vec2& destpos, float& cocosAngle)
{
    
	switch (Direction)
	{
	case MOVE_LEFT:
		destpos.x -= MOVE_SIZE;
		cocosAngle = 270;
		break;
	case MOVE_RIGHT:
		destpos.x += MOVE_SIZE;
		cocosAngle = 90;
		break;
	case MOVE_UP:
		destpos.y += MOVE_SIZE;
		break;
	case MOVE_DOWN:
		destpos.y -= MOVE_SIZE;
		cocosAngle = 180;
		break;
	default:
		break;
	}

}

void HelloWorld::animateEnemy(Sprite *enemy)
{
	// speed of the enemy
	float actualDuration = 0.2f;
	auto pos = enemy->getPosition();
	auto destpos = pos;

	Vec2 position;
	float cocosAngle = 0;
	Move_Direction Direction = (Move_Direction)enemy->getTag();
	move_f(Direction, destpos, cocosAngle);
	if (IsEnemyCollidable(destpos, enemy))
	{
		position = destpos - pos;
	}
	else
	{
		
		std::vector<Move_Direction> Directions;
		if (Direction == MOVE_LEFT || Direction == MOVE_RIGHT)
		{
			if (int(CCRANDOM_0_1() * 10000) % 2 == 0)
			{
				Directions.push_back(MOVE_UP);
				Directions.push_back(MOVE_DOWN);
			}
			else
			{
				Directions.push_back(MOVE_DOWN);
				Directions.push_back(MOVE_UP);
			}
			if (Direction == MOVE_LEFT)
				Directions.push_back(MOVE_RIGHT);
			else
				Directions.push_back(MOVE_LEFT);
		}
		else
		{
			if (int(CCRANDOM_0_1() * 10000) % 2 == 0)
			{
				Directions.push_back(MOVE_LEFT);
				Directions.push_back(MOVE_RIGHT);
			}
			else{
				Directions.push_back(MOVE_RIGHT);
				Directions.push_back(MOVE_LEFT);
			}
			if (Direction == MOVE_UP)
				Directions.push_back(MOVE_DOWN);
			else
				Directions.push_back(MOVE_UP);
		}
		for (Move_Direction Dir : Directions)
		{
			destpos = pos;
			move_f(Dir, destpos, cocosAngle);
			if (IsEnemyCollidable(destpos,	enemy))
			{
				enemy->setTag(Dir);
				position = destpos - pos;
				break;
			}
		}
	}

	//enemy->setRotation(cocosAngle);
	
	if (!position.isZero())
	{
		Point tileCoord = this->tileCoordForPosition(destpos);
		enemy->setUserData((void*)(int)(tileCoord.x * 100 + tileCoord.y));
	}
	auto actionMove = MoveBy::create(actualDuration, position);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::enemyMoveFinished, this));
	enemy->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
// 	// Create the actions
// 	auto position = (_player->getPosition() - enemy->getPosition()).normalize() * 10;
// 	auto actionMove = MoveBy::create(actualDuration, position);
// 	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::enemyMoveFinished, this));
// 	enemy->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
};

void HelloWorld::setPlayerPosition(Point position)
{
	_player->setPosition(position);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	_BeganPos = this->convertToNodeSpace(touchLocation);
	return true;
}

void HelloWorld::playerMoveFinished(Object *pSender)
{
	Sprite *player = (Sprite *)pSender;
	
	this->animatePlayer(player);
}

// a method to move the enemy 10 pixels toward the player
void HelloWorld::animatePlayer(Sprite *player)
{
	auto pos = player->getPosition();
	auto destpos = pos;
	float actualDuration = 0.1f;
	

	float cocosAngle = 0;
	
	switch (_Direction)
	{
	case MOVE_LEFT:
		destpos.x -= MOVE_SIZE;
		cocosAngle = 270;
		break;
	case MOVE_RIGHT:
		destpos.x += MOVE_SIZE;
		cocosAngle = 90;
		break;
	case MOVE_UP:
		destpos.y += MOVE_SIZE;
		break;
	case MOVE_DOWN:
		destpos.y -= MOVE_SIZE;
		cocosAngle = 180;
		break;
	default:
		break;
	}
	Vec2 position;
	if (IsCollidable(destpos))
	{
		position = destpos - pos;
	}
	
	player->setRotation(cocosAngle);
	auto actionMove = MoveBy::create(actualDuration, position);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::playerMoveFinished, this));
	player->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

Point HelloWorld::tileCoordForPosition(Point position)
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return Point(x, y);
}

bool HelloWorld::IsEnemyCollidable(Point position, Sprite *enemy)
{
	static auto __left = enemy->getContentSize().width / 2;
	static auto __right = (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - enemy->getContentSize().width / 2;
	static auto __top = (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - enemy->getContentSize().height / 2;
	static auto __bottom = enemy->getContentSize().height / 2;
	if (position.x < __left - 5)
		return false;
	if (position.x > __right + 5)
		return false;
	if (position.y < __bottom - 5)
		return false;
	if (position.y > __top + 5)		
		return false;

	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {
			auto collision = properties["Collidable"].asString();
			if ("True" == collision) {
				return false;
			}


		}
	}

	int tileGidland = _land->getTileGIDAt(tileCoord);
	if (tileGidland) {
		auto properties = _tileMap->getPropertiesForGID(tileGidland).asValueMap();
		if (!properties.empty()) {
			return false;
		}
	}

	for (Sprite *target : _enemies) {
		if (target == enemy)	continue;
        int temp = 0;
        
        
		void* a = target->getUserData();
        memcpy(&temp, &a, sizeof(void*));
		Point targetCoord(temp/100,temp%100);
		if (tileCoord == targetCoord)
		{
			return false;
		}
	}
	return true;
}

bool HelloWorld::IsCollidable(Point position)
{
	static auto __left = _player->getContentSize().width / 2;
	static auto __right = (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - _player->getContentSize().width / 2;
	static auto __top = (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - _player->getContentSize().height / 2;
	static auto __bottom = _player->getContentSize().height / 2;
	if (position.x < __left)		return false;
	if (position.x > __right )		return false;
	if (position.y < __bottom - 5)	return false;
	if (position.y > __top + 5 )		return false;

	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {
			auto collision = properties["Collidable"].asString();
			if ("True" == collision) {
				return false;
			}


		}
	}

	int tileGidland = _land->getTileGIDAt(tileCoord);
	if (tileGidland) {
		auto properties = _tileMap->getPropertiesForGID(tileGidland).asValueMap();
		if (!properties.empty()) {
			auto collectable = properties["Collectable"].asString();
			if ("True" == collectable) {
				_land->removeTileAt(tileCoord);
			}
			if ("Pick" == collectable) {
				_land->removeTileAt(tileCoord);
				_numCollected++;
				if (_numCollected == 4)
					win();
			}

		}
	}
	

	return true;
}

void HelloWorld::win()
{
	GameOverScene*  gameOverScene = GameOverScene::create();
 	gameOverScene->getLayer()->getLabel()->setString("You Win!");
 	Director::getInstance()->replaceScene(gameOverScene);
}
void HelloWorld::lose()
{
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Lose!");
	Director::getInstance()->replaceScene(gameOverScene);
}
void HelloWorld::testCollisions(float dt)
{
	for (Sprite *target : _enemies) {
		auto targetRect = Rect(
			target->getPosition().x - (target->getContentSize().width / 2),
			target->getPosition().y - (target->getContentSize().height / 2),
			target->getContentSize().width,
			target->getContentSize().height);
		if (targetRect.containsPoint(_player->getPosition())) {
			this->lose();
		}
	}
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);
	auto diff = touchLocation - _BeganPos;
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			_Direction = MOVE_RIGHT;
		}
		else if (diff.x < 0)
		{
			_Direction = MOVE_LEFT;
		}
	}
	else {
		if (diff.y > 0) {
			_Direction = MOVE_UP;
		}
		else if (diff.y < 0)
		{
			_Direction = MOVE_DOWN;
		}
	}

}

void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);
	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

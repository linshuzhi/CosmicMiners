#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


enum Move_Direction{
	MOVE_DEF = 0,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	void setViewPointCenter(cocos2d::Point position);
	void setPlayerPosition(cocos2d::Point position);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void playerMoveFinished(cocos2d::Object *pSender);
	void animatePlayer(cocos2d::Sprite *player);

	bool IsCollidable(cocos2d::Point position);
	bool IsEnemyCollidable(cocos2d::Point position, cocos2d::Sprite *enemy);
	
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);
	void win();
	void lose();
	void addEnemyAtPos(cocos2d::Point pos);
	void enemyMoveFinished(cocos2d::Object *pSender);
	void animateEnemy(cocos2d::Sprite *enemy);
	void testCollisions(float dt);
private:
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
	cocos2d::TMXLayer *_meta;
	cocos2d::TMXLayer *_land;
	cocos2d::Sprite *_player;
	cocos2d::Vec2 _BeganPos;

	Move_Direction _Direction;
	int _numCollected;

	cocos2d::Vector<cocos2d::Sprite *> _enemies;
};

#endif // __HELLOWORLD_SCENE_H__

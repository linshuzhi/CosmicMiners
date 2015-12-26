//
//  GameManager.h
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#ifndef __RunRound__GameManager__
#define __RunRound__GameManager__
#include "MapModel.h"
#include "vector"


class GameLayer;
class GameManager{
public:
    GameManager();
    ~GameManager();
    static GameManager* getInstance();
    
    void startLevel(int level);
    MapModel getMapData(int level);
    int getCurLevel(){
        return _level;
    }
    void setLevelSuccess();
    void toBack();
    void toNext();
    void toReplay();
    void readTmx(int level,MapModel& info);
    const std::vector<cocos2d::Point>& getLandPoints();
    const std::vector<cocos2d::Point>& getWallPoints();
    const std::vector<cocos2d::Point>& getDevilPoints();
    const std::vector<cocos2d::Point>& getDiamondsRedPoints();
    const std::vector<cocos2d::Point>& getDiamondsBluePoints();
    const std::vector<cocos2d::Point>& getBallPoints();
    cocos2d::Point getHeroPoints();
    cocos2d::Point getDoorPoints();
    int getItemWidth();
    cocos2d::Point getRealPoint(cocos2d::Point point);
    
    void addScore(int score);
    void reset();
    void setGameLayer(GameLayer* gameLayer);
    void showWinLayer();
    void showLoseLayer();
private:
    void init();

private:
    GameLayer* _gameLayer;
    static GameManager* _instance;
    MapModel _mapInfo;
    int _level;
    int _score;         //当前的分数
};

#endif /* defined(__RunRound__GameManager__) */

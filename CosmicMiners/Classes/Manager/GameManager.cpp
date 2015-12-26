//
//  GameManager.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "GameManager.h"
#include "../Utils/StringResources.h"
#include "UserLevelManager.h"
#include "DirectorManager.h"
#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "../Utils/BranchTools.h"
#include "ItemManager.h"
#include "../UI/GameLayer/GameLayer.h"
using namespace tinyxml2;
USING_NS_CC;


namespace  {
    const int kMapSize = 400;
    const char* kMapFileFormat = "map/map_%d.tmx";
    const int kItemWidth = 30;
}
GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
: _level(0)
, _score(0)
, _gameLayer(nullptr)
{
    
}


GameManager::~GameManager(){
    
}


GameManager* GameManager::getInstance(){
    if (!_instance) {
        _instance = new GameManager();
        _instance->init();
    }
    return _instance;
}

void GameManager::init(){
    
}
void GameManager::reset(){
    _level = 0;
    _score = 0;
    _mapInfo.reset();
}
void GameManager::startLevel(int level){
    
    reset();
    _level = level;
    readTmx(level,_mapInfo);
    ItemManager::getInstance()->reset();
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_GAME);
}
void GameManager::readTmx(int level,MapModel& info){
    info.level = level;
    std::string filename = StringUtils::format(kMapFileFormat,level);

    auto data = FileUtils::getInstance()->getStringFromFile(filename);
    
    XMLDocument* myDocment = new tinyxml2::XMLDocument();
    //加载文件
    myDocment->Parse(data.c_str());
    
    tinyxml2::XMLElement* rootElement = myDocment->RootElement();
    
    
    XMLElement* layerElement = rootElement->FirstChildElement();
    
    while (layerElement) {
        
        auto  name = layerElement->Attribute("name");
        if(name == nullptr)
            break;
        std::string att = name;
        if(att == "land"){
            int width = layerElement->IntAttribute("width");
            int height = layerElement->IntAttribute("height");
            _mapInfo.width = width;
            _mapInfo.height = height;
            auto datas = layerElement->FirstChildElement();
            if(!datas){
                break;
            }
            auto tiles = datas->FirstChildElement();
            int indexW = 0;
            int indexH = height - 1;
            while (tiles) {
                
                int gid = tiles->IntAttribute("gid");
                switch (gid) {
                    case 1:
                        _mapInfo._landPoints.push_back(Point(indexW,indexH));
                        break;
                    case 2:
                        _mapInfo._ballPoints.push_back(Point(indexW,indexH));
                        break;
                    case 3:
                        _mapInfo._wallPoints.push_back(Point(indexW,indexH));
                        break;
                    case 4:
                        _mapInfo._diamondsBluePoints.push_back(Point(indexW,indexH));
                        break;
                    case 5:
                        _mapInfo._diamondsRedPoints.push_back(Point(indexW,indexH));
                        break;
                    case 6:
                        _mapInfo._devilPoints.push_back(Point(indexW,indexH));
                        break;
                    case 7:
                        _mapInfo._doorPoint = Point(indexW,indexH);
                        break;
                    case 8:
                        _mapInfo._heroPoint = Point(indexW,indexH);
                        break;
                    default:
                        break;
                }
                
                indexW++;
                if (indexW == width) {
                    indexW = 0;
                    indexH--;
                }
                tiles = tiles->NextSiblingElement();
            }
            
        }else if(att == "BasicItem"){
            auto tiles = layerElement->FirstChildElement();
            while (tiles) {
                auto  id = tiles->IntAttribute("id");
                if (id == 6) {
                    auto properties = tiles->FirstChildElement();
                    auto property = properties->FirstChildElement();
                    int count = property->IntAttribute("value");
                    _mapInfo.needScore = count;
                }
                tiles = tiles->NextSiblingElement();
            }
            
        }
        layerElement = layerElement->NextSiblingElement();
        
    }
}

const std::vector<cocos2d::Point>& GameManager::getLandPoints(){
    return _mapInfo._landPoints;
}

const std::vector<cocos2d::Point>& GameManager::getWallPoints(){
    return _mapInfo._wallPoints;
}


const std::vector<cocos2d::Point>& GameManager::getDevilPoints(){
    return _mapInfo._devilPoints;
}
const std::vector<cocos2d::Point>& GameManager::getDiamondsRedPoints(){
    return _mapInfo._diamondsRedPoints;
}
const std::vector<cocos2d::Point>& GameManager::getDiamondsBluePoints(){
    return _mapInfo._diamondsBluePoints;
}
const std::vector<cocos2d::Point>& GameManager::getBallPoints(){
    return _mapInfo._ballPoints;
}
cocos2d::Point GameManager::getHeroPoints(){
    return _mapInfo._heroPoint;
}
cocos2d::Point GameManager::getDoorPoints(){
    return _mapInfo._doorPoint;
}

cocos2d::Point GameManager::getRealPoint(cocos2d::Point point){
    static Size visibleSize = Director::getInstance()->getVisibleSize();
    static Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Point retPoint;
    retPoint.x = origin.x + point.x * kItemWidth + kItemWidth / 2;
    retPoint.y = origin.y + point.y * kItemWidth + kItemWidth / 2;
    return retPoint;
}

int GameManager::getItemWidth(){
    return kItemWidth;
}

MapModel GameManager::getMapData(int level){
    return _mapInfo;
}

void GameManager::addScore(int score){
    _score += score;
    if (_score >= _mapInfo.needScore) {
        ItemManager::getInstance()->lightenDoor();
    }
}

void GameManager::toBack(){
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_LEVEL);
}
void GameManager::toNext(){
    std::string filename = StringUtils::format(kMapFileFormat,_level+1);
    if(!FileUtils::getInstance()->isFileExist(filename)){
        startLevel(_level);
        return;
    }
    startLevel(_level + 1);
}
void GameManager::toReplay(){
    startLevel(_level);
}

void GameManager::setLevelSuccess(){
    UserLevelManager::getInstance()->setLevelSuccess(_level + 1);
}

void GameManager::setGameLayer(GameLayer* gameLayer){
    _gameLayer = gameLayer;
}

void GameManager::showWinLayer(){
    _gameLayer->showWinLayer();
}
void GameManager::showLoseLayer(){
    _gameLayer->showLoseLayer();
}


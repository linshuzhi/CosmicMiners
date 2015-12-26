//
//  MapModel.h
//  RunRound
//
//  Created by LinShulong on 15/11/23.
//
//

#ifndef __RunRound__MapModel__
#define __RunRound__MapModel__

#include "cocos2d.h"
#include <vector>

struct MapModel {
    int level;
    int width;
    int height;
    int needScore;
    std::vector<cocos2d::Point> _landPoints;
    std::vector<cocos2d::Point> _wallPoints;
    
    std::vector<cocos2d::Point> _diamondsRedPoints;
    std::vector<cocos2d::Point> _diamondsBluePoints;
    
    std::vector<cocos2d::Point> _devilPoints;
    std::vector<cocos2d::Point> _ballPoints;
    cocos2d::Point _heroPoint;
    cocos2d::Point _doorPoint;
    
    MapModel(){
        level = 0;
        width = 0;
        height = 0;
        needScore = 0;
    }
    void reset(){
        level = 0;
        width = 0;
        height = 0;
        needScore = 0;
        _landPoints.clear();
        _wallPoints.clear();
        _diamondsRedPoints.clear();
        _diamondsBluePoints.clear();
        _devilPoints.clear();
        _ballPoints.clear();
        _heroPoint.setZero();
        _doorPoint.setZero();
    }
    
};

#endif /* defined(__RunRound__MapModel__) */

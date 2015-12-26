//
//  TouchManager.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/20.
//
//

#include "TouchManager.h"
std::vector<TouchManagerDelegate*> TouchManager::_delegates;

void TouchManager::touchChange(TouchManagerDelegate::direction dir){
    
    updateData(dir);
}

void TouchManager::addDelegate(TouchManagerDelegate* delegate){
    _delegates.push_back(delegate);
}
void TouchManager::deleteDelegate(TouchManagerDelegate* delegate){
    

    for (std::vector<TouchManagerDelegate*>::iterator iter = _delegates.begin(); iter != _delegates.end(); iter++) {
        if (delegate == *iter) {
            _delegates.erase(iter);
            return;
        }
    }
}

void TouchManager::updateData(TouchManagerDelegate::direction dir){

    for(TouchManagerDelegate* delegate : _delegates){
        delegate->onTouchChange(dir);
    }
}




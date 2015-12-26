//
//  TouchManager.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/20.
//
//

#ifndef TouchManager_h
#define TouchManager_h

#include <vector>
#include "TouchManagerDelegate.h"

class TouchManager{
public:

    static void touchChange(TouchManagerDelegate::direction dir);
    static void updateData(TouchManagerDelegate::direction dir);
    static void addDelegate(TouchManagerDelegate* delegate);
    static void deleteDelegate(TouchManagerDelegate* delegate);
    
private:
    static std::vector<TouchManagerDelegate*> _delegates;
};

#endif /* TouchManager_h */

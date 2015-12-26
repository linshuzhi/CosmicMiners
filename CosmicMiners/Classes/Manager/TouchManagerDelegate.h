//
//  TouchManagerDelegate.h
//  CosmicMiners
//
//  Created by LinShulong on 15/12/20.
//
//

#ifndef TouchManagerDelegate_h
#define TouchManagerDelegate_h
class TouchManagerDelegate{
public:
    enum direction{
        direction_none = 0,
        direction_left,
        direction_up,
        direction_right,
        direction_down,
    };
    virtual void onTouchChange(direction dir) = 0;
};

#endif /* TouchManagerDelegate_h */

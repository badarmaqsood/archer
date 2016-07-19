//
//  Board.h
//  board
//
//  Created by Tin on 7/15/16.
//
//

#ifndef Board_h
#define Board_h

#include "cocos2d.h"


using namespace cocos2d;


class Board : public Node
{
    
    
private:
    
    //screen variables
    Size visibleSize ;
    Vec2 origin;
    
    //character variables
    Sprite* board;
    
    
    
public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Board);
    
    //loading Assets
    
    void loadAssets();
    
    //getters for character sprites
    Sprite* getBoard();
    
    
    
};




#endif /* Board_h */

//
//  Archer.h
//  archer
//
//  Created by Tin on 7/15/16.
//
//

#ifndef Archer_h
#define Archer_h

#include "cocos2d.h"


using namespace cocos2d;


class Archer : public Node
{
    
    
private:
    
    //screen variables
    Size visibleSize ;
    Vec2 origin;
    
    //character variables
    Sprite* playerBottomHalf;
    Sprite* playerUpperHalf;
    Sprite* PlayerArm;
    
    
    
    
public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Archer);
    
    //loading Assets
    
    void loadAssets();
    
    //getters for character sprites
    Sprite* getPlayerUpperBody();
    Sprite* getPlayerLowerBody();
    Sprite* getPlayerArm();


    
};




#endif /* Archer_h */

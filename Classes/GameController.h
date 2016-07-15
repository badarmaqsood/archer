//
//  GameController.h
//  archer
//
//  Created by Tin on 7/15/16.
//
//

#ifndef GameController_h
#define GameController_h


#include "cocos2d.h"
#include "Archer.h"
using namespace cocos2d;



class GameController : public Node
{
    
    
private:
    
    //screen variables
    Size visibleSize ;
    Vec2 origin;
    
    
    
public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameController);
    
    //loading Assets
    void loadAssets();
    
    //asset variables
    Sprite* background;
    Sprite* playerBottomHalf;
    Sprite* playerUpperHalf;
    Sprite* playerHand;
    
    //layer for joining player body parts
    Layer* player_layer;
    
    //layer for upper body + arm
    Layer* upper_body_layer;
    
    void drawBorder(Node* a_node, Color4F a_color4f);
    
    
    
};


#endif /* GameController_h */

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
#include "Board.h"
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
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    bool onTouchEnded(Touch* touch, Event* event);
    
    bool onContactBegin(PhysicsContact & contact);
    
    //loading Assets
    void loadAssets();
    
    //asset variables
    Sprite* background;
    Sprite* playerBottomHalf;
    Sprite* playerUpperHalf;
    Sprite* playerHand;
    Sprite* arrow;
    Sprite* touch_start_circle;
    Sprite* touch_end_circle;
    Sprite* board;
    Sprite* noTipArrow;
    
    
    //physicsBody for arrow body
    PhysicsBody* arrow_body;
    
    //physicsBody for board
    PhysicsBody* board_body;
    
    // for arrow_ direction
    Vec2 arrow_direction;
    
    //for player arm base position
    float player_arm_position_x;
    
    
    
    //for arrow base position
    float arrow_position_x;
    float arrow_position_y;
    
    //temp ... delete them afterwards
    CCLabelTTF* label;
    
    
    //layer for joining player body parts
    Layer* player_layer;
    
    //layer for upper body + arm
    Layer* upper_body_layer;
    
    //layer for board
    Layer* board_layer;
    
    void drawBorder(Node* a_node, Color4F a_color4f);
    
    //for rotation of upper body
    void rotateUpperBody(float rotation_angle);
    
    //for movement of arrow + arm
    void moveArmAndArrow(float move_distance);
    
    //for resetting the player arm + arrow position
    void resetArmAndArrowPosition();
    
    //checking for first touch
    bool bool_first_touch;
    
    //speed of board movement
    float board_speed;
    
    
    //for board movement
    void moveBoard();
    
    //hoarse function for board movement
    void _moveBoard(float dt);
    
};


#endif /* GameController_h */

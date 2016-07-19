//
//  GameController.cpp
//  archer
//
//  Created by Tin on 7/15/16.
//
//

#include <stdio.h>
#include "GameController.h"
#include "Board.h"



Scene* GameController::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    //setting gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0, -490));
    
    
    // 'layer' is an autorelease object
    auto layer = GameController::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool GameController::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    
    bool_first_touch = true;
    
    //screen variables
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    
    
    //catching touch
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(GameController::onTouchBegan, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(GameController::onTouchMoved, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(GameController::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    
    
    
    //designing background
    loadAssets();
    
    //moving board
    moveBoard();
    
    return true;
}


void GameController::loadAssets()
{
    //background
    background = Sprite::create("score.png");
    background->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScale(1.7);
    this->addChild(background);
    
    //layer for joining player parts
    player_layer = Layer::create();
    
    //initializing archer instance
    Archer * archer = Archer::create();
    
    //initializing player body sprites
    playerBottomHalf = archer->getPlayerLowerBody();
    playerUpperHalf = archer->getPlayerUpperBody();
    playerHand = archer->getPlayerArm();
    playerBottomHalf->setAnchorPoint(Vec2(0, 0));
    
    //adding player body sprites to the player layer
    player_layer->addChild(playerBottomHalf);
    
    
    //setting player layer position on the screen
    player_layer->setPosition(Vec2(origin.x + (visibleSize.width * 0.8) , origin.y + (visibleSize.height * 0.04)));
    player_layer->setContentSize(Size(MAX(playerBottomHalf->getContentSize().width, playerUpperHalf->getContentSize().width)  , playerBottomHalf->getContentSize().height + playerUpperHalf->getContentSize().height/2));
    
    this->addChild(player_layer);
    
    //setting player upper body layer
    upper_body_layer = Layer::create();
    upper_body_layer->setContentSize(playerUpperHalf->getContentSize());
    upper_body_layer->ignoreAnchorPointForPosition(false);
    upper_body_layer->setAnchorPoint(Vec2(1,0.5));
    upper_body_layer->setPosition(Vec2(playerBottomHalf->getContentSize().width * 0.8, playerBottomHalf->getContentSize().height ));
    
    //adding the laft half of the upper body to the upper layer
    upper_body_layer->addChild(playerUpperHalf);
    playerUpperHalf->setPosition(Vec2(0, 0));
    playerUpperHalf->setAnchorPoint(Vec2(0  , 0));
    
    
    //adding the arm to the upper body layer
    upper_body_layer->addChild(playerHand);
    playerHand->setPosition(Vec2(playerBottomHalf->getContentSize().width/2, playerUpperHalf->getContentSize().height * 0.55));
    playerHand->setAnchorPoint(Vec2(0, 1));
    
    
    //adding the bow part
    DrawNode* bowPart = DrawNode::create();
    upper_body_layer->addChild(bowPart);
    bowPart->drawLine(Vec2(playerUpperHalf->getContentSize().width * 0.44, playerUpperHalf->getContentSize().height), Vec2(playerUpperHalf->getContentSize().width * 0.44, 0), Color4F::WHITE);
    
    
    
    //initializing arrow
    arrow = Sprite::create("arrow.png");
    upper_body_layer->addChild(arrow);
    arrow->setPosition(Vec2(0, upper_body_layer->getContentSize().height/2));
    
    
    
    //adding the upper layer to the main player layer
    player_layer->addChild(upper_body_layer);
    
    
    
    //for storing player arm base position
    player_arm_position_x = playerHand->getPosition().x;
    
    //for storing arrow base position
    arrow_position_x = arrow->getPosition().x;
    arrow_position_y = arrow->getPosition().y;
   
    //setting up sprite for touch start touch position
    touch_start_circle = Sprite::create("white_dot.png");
    this->addChild(touch_start_circle);
    touch_start_circle->setVisible(false);
    
    //setting up sprite for touch end position
    touch_end_circle = Sprite::create("white_dot.png");
    this->addChild(touch_end_circle);
    touch_end_circle->setVisible(false);
    
    
    
    //layer for board
    board_layer = Layer::create();
    this->addChild(board_layer);
    
    //initializing board instance
     Board * target=  Board::create();
    
    //initializing board sprite
    board = target->getBoard();
    board_layer->addChild(board);
    board->setAnchorPoint(Vec2(0, 0));
    
    //positioning board
    board_layer->setContentSize(Size(board->getContentSize()));
    board_layer->setPosition(Vec2(visibleSize.width * 0.05, visibleSize.height/2));
    
    
    //scaling board layer
    board_layer->setScale(0.5);
    
    //adding physics body to board
    board_body = PhysicsBody::createBox(board_layer->getContentSize());
    board_body->setDynamic(true);
    board_body->setMass(10000000000000);
    board_body->setGravityEnable(false);
    board_body->setContactTestBitmask(1);
    board_layer->setPhysicsBody(board_body);

    
    
    
    
    
    drawBorder(board_layer, Color4F::WHITE);
    drawBorder(board, Color4F::WHITE);

    
    // for debugging .... delete it at the end
    label = CCLabelTTF::create("Hello World", "Helvetica", 22,
                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->addChild(label);
    label->setPosition(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2);
    
    
}




void GameController::drawBorder(Node* a_node, Color4F a_color4f)
{
    float height = a_node->getContentSize().height;
    float width = a_node->getContentSize().width;
    
    DrawNode* pDrawNode = DrawNode::create();
    pDrawNode->drawRect( Vec2(0.0f, 0.0f), Vec2(width, height), a_color4f);
    
    a_node->addChild(pDrawNode, -1);
}


//OnTouchBegan

bool GameController::onTouchBegan(Touch* touch, Event* event)
{
    log("onTouchBegan");
    
    
    resetArmAndArrowPosition();
    
    //setting start touch cirlcle and making it visible
    touch_start_circle->setPosition(touch->getStartLocation());
    touch_start_circle->setVisible(true);
    
  
    return true;
}


//OnTouchMoved
void GameController::onTouchMoved(Touch* touch, Event* event)
{
    
    touch_end_circle->setPosition(touch->getLocation());
    touch_end_circle->setVisible(true);
    
    //for touch start
    float touch_start_position_x = touch->getStartLocation().x;
    float touch_start_position_y = touch->getStartLocation().y;
    
    //for current touch
    float touch_current_position_x = touch->getLocation().x;
    float touch_current_position_y = touch->getLocation().y;
    
    //for total distance moved during touch
    float touch_distance_x = touch_current_position_x - touch_start_position_x;
    float touch_distance_y = touch_current_position_y - touch_start_position_y;
    
    //logic for rotating the upper body
    if(touch_distance_y >= 0 && touch_distance_y/4 <= 25)
    {
        rotateUpperBody(touch_distance_y/4);
    }
    else if( touch_distance_y <0 && touch_distance_y/4 >= -15)
    {
        rotateUpperBody(touch_distance_y/4);
    
    }
    
    
    
    //logic for moving the left arm of the player
    if(touch_distance_x >= 0 && touch_distance_x/10 <= 17.6)
    {
        moveArmAndArrow(touch_distance_x/10);
       
    }
    
    arrow_direction = Vec2(touch_distance_x, touch_distance_y);
    
    
    //log("onTouchMoved");
}


//OnTouchEnded
bool GameController::onTouchEnded(Touch* touch, Event* event)
{
    log("onTouchEnded");
    
    //hiding the touch circles
    touch_start_circle->setVisible(false);
    touch_end_circle->setVisible(false);
    
    
    // deploying physics body to arrow
    arrow_body = PhysicsBody::createBox(arrow->getContentSize());
    arrow_body->setDynamic(true);
    arrow_body->setGravityEnable(true);
    arrow_body->setContactTestBitmask(1);
    

    
    
    //arrow->getPhysicsBody()->setGravityEnable(true);
    if(arrow_body)
    {
    arrow->setPhysicsBody(arrow_body);
    arrow_body->setVelocity(Vec2(-(arrow_direction.x) * 4, arrow_direction.y) * 4);
    }
    
    
    return true;
}


//for rotating upper body
void GameController::rotateUpperBody(float rotation_angle)
{
    upper_body_layer->setRotation(rotation_angle);

}

//for moving arm + arrow
void GameController::moveArmAndArrow(float move_distance)
{
    playerHand->setPosition(Vec2(player_arm_position_x + move_distance, playerHand->getPosition().y));
    arrow->setPosition(Vec2(arrow_position_x + move_distance, arrow->getPosition().y));
}

//for resetting arm + arrow position
void GameController::resetArmAndArrowPosition()
{
    if(!bool_first_touch)
    {
       //initializing a new arrow
        upper_body_layer->removeChild(arrow);
        arrow = nullptr;
        arrow = Sprite::create("arrow.png");
        upper_body_layer->addChild(arrow);
       
    }
    bool_first_touch = false;
    
    //resetting player arm and arrow position
    playerHand->setPosition(Vec2(player_arm_position_x, playerHand->getPosition().y));
    arrow->setPosition(Vec2(arrow_position_x, arrow_position_y));

    
}


void GameController::moveBoard()
{
    //setting board speed
    board_speed = 3;
    this->schedule(schedule_selector(GameController::_moveBoard), 0.1);
    
}

void GameController::_moveBoard(float dt)
{
    
    float board_current_position_y = board_layer->getPosition().y;
    if(board_current_position_y >= 155 || board_current_position_y <= 35)
    {
        board_speed = board_speed * -1;
    }
    
    MoveBy* move = MoveBy::create(0.1, Vec2(0, board_speed));
    board_layer->runAction(move);
    label->setString(std::to_string(board_current_position_y));
    //board_current_position_y = board_layer->getPosition().y;
    
}




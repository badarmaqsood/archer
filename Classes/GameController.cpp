//
//  GameController.cpp
//  archer
//
//  Created by Tin on 7/15/16.
//
//

#include <stdio.h>
#include "GameController.h"



Scene* GameController::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    //setting gravity
    
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
    
    
    //screen variables
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    //designing background
    loadAssets();
    
    
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
    player_layer->setPosition(Vec2(origin.x + (visibleSize.width * 0.8) , origin.y + (visibleSize.height * 0.1)));
    player_layer->setContentSize(Size(MAX(playerBottomHalf->getContentSize().width, playerUpperHalf->getContentSize().width)  , playerBottomHalf->getContentSize().height + playerUpperHalf->getContentSize().height/2));
    
    this->addChild(player_layer);
    
    //setting player upper body layer
    upper_body_layer = Layer::create();
    upper_body_layer->setContentSize(playerUpperHalf->getContentSize());
    
    
    
    
    player_layer->addChild(upper_body_layer);
    upper_body_layer->setPosition(Vec2(playerBottomHalf->getContentSize().width * 0.8, playerBottomHalf->getContentSize().height * 1.1));
    upper_body_layer->addChild(playerUpperHalf);
    
    upper_body_layer->ignoreAnchorPointForPosition(false);
    
    playerUpperHalf->setPosition(Vec2(0, 0));
    
    
    upper_body_layer->setAnchorPoint(Vec2(1,0.5));
    playerUpperHalf->setAnchorPoint(Vec2(0  , 0));
    
    

    drawBorder(upper_body_layer, Color4F::WHITE);
    drawBorder(player_layer, Color4F::WHITE);

    
    
    
}


void GameController::drawBorder(Node* a_node, Color4F a_color4f)
{
    float height = a_node->getContentSize().height;
    float width = a_node->getContentSize().width;
    
    DrawNode* pDrawNode = DrawNode::create();
    pDrawNode->drawRect( Vec2(0.0f, 0.0f), Vec2(width, height), a_color4f);
    
    a_node->addChild(pDrawNode, -1);
}


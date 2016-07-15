//
//  Archer.cpp
//  archer
//
//  Created by Tin on 7/15/16.
//
//

#include <stdio.h>
#include "Archer.h"



Scene* Archer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    //setting gravity
    
    // 'layer' is an autorelease object
    auto layer = Archer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool Archer::init()
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


// function to initialize assets
void Archer::loadAssets()
{
    playerBottomHalf = Sprite::create("body.png");
    playerUpperHalf = Sprite::create("bow_upper.png");
    PlayerArm = Sprite::create("arm.png");
    
}



//getter for player arm
Sprite* Archer::getPlayerArm()
{
    if(PlayerArm)
    {
        return PlayerArm;
    }
    
}


//getter for player lower body
Sprite* Archer::getPlayerLowerBody()
{
    if(playerBottomHalf)
    {
        return playerBottomHalf;
    }
}


//getter for player upper body
Sprite* Archer::getPlayerUpperBody()
{
    if(PlayerArm)
    {
        return playerUpperHalf;
    }
}




//
//  Archer.cpp
//  archer
//
//  Created by Tin on 7/15/16.
//
//

#include <stdio.h>
#include "Board.h"



Scene* Board::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    //setting gravity
    
    // 'layer' is an autorelease object
    auto layer = Board::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool Board::init()
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
void Board::loadAssets()
{
    board = Sprite::create("target.png");
    
}



//getter for player board
Sprite* Board::getBoard()
{
    if(board)
    {
        return board;
    }
    
}




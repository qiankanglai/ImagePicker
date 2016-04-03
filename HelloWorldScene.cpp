#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    ImagePicker::getInstance()->pickImage(this);
    
    return true;
}


void HelloWorld::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    auto sprite = Sprite::createWithTexture(result);
    sprite->setPosition(0, 0);
    this->addChild(sprite);
}
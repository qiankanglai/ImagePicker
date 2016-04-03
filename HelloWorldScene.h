#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/ImagePicker/ImagePicker.h"

class HelloWorld : public cocos2d::Layer, public cocos2d::ImagePickerDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void didFinishPickingWithResult(cocos2d::Texture2D* result);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

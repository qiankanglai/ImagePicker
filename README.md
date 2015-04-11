ImagePicker
===========

**The newest code can be found here: https://github.com/cocos2d/cocos2d-x/pull/11344. I've put all the codes into cocos2d-x 3.5 along with tests. Also win8.1-universal is supported now.**

ImagePicker utility for cocos2d-x 3.5 

**Attention**
- iOS 8 may crash with default setting. Please check out this issue [iPhone 5S Error](https://github.com/qiankanglai/ImagePicker/issues/2) here. I haven't found an elegant way to fix this, and any pull request is welcomed!

This utility lets you load images from device gallery and load it to your application as a Texture2D. You may draw Sprite with this texture or use it in other ways.

The origin project is https://github.com/Losiowaty/ImagePicker, and I clear the whole project, in addition to:

- add support for iPhone (combined with iPad)
- add support for Win32/OSX/Win8.1
- put Android support together
- take advantage of ccx 3.5 API
- Javascript Binding (lua binding to be done)

The image is loaded by platform API and deliveried to ccx in memory directly. No repeated IO is needed.

usage example screenshots: http://qiankanglai.me/project/2014/04/14/cocos2dx-ImagePicker/

Guide
=====
Installation
------------

1. iOS/Mac

Add the following sources into project:

- ImagePicker.h, ImagePicker.cpp
- ImagePickerImpl.h, ImagePickerImpl.mm
- ImagePicker-ios.h, ImagePicker-ios.mm (iOS only)

2. Android/Win32/Win8.1

- ImagePicker.h, ImagePicker.cpp
- ImagePickerImpl.h, ImagePickerImpl.cpp
- Cocos2dxImagePicker.java (Android only)
- App.xaml.cs (Win8.1 phone version only)

3. JSB

- jsb_cocos2dx_extension_ImagePicker.hpp
- jsb_cocos2dx_extension_ImagePicker.cpp

Usage
-----

Just call `ImagePicker::getInstance()->pickImage()` and pass in your delegate. If the image is picked successfully, your delegate will receive the corresponding Texture2D, or nullptr otherwise.

For cocos2d-JS users: add `sc->addRegisterCallback(register_all_cocos2dx_extension_ImagePicker);` in AppDelegate.cpp,

    var delegator = new jsb.ImagePickerDelegate();
    delegator.didFinishPickingWithResult = function(texture){
        if(texture) {
            var sprite = cc.Sprite.createWithTexture(texture);
            var winSize = cc.director.getWinSize();
            sprite.x = winSize.width / 2;
            sprite.y = winSize.height / 2;
            self.addChild(sprite);
        }
        else {
            cc.log("ImagePicker return null");
        }
    };
    var picker = jsb.ImagePicker.getInstance();
    picker.pickImage(delegator);

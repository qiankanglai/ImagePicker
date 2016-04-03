ImagePicker
===========

I made a [Pull Request](https://github.com/cocos2d/cocos2d-x/pull/11344) before and seems cocos doesn't need it :) So I just put all codes along with test here.

ImagePicker utility for cocos2d-x v3

**Attention**
- iOS 8 may crash with default setting. Please check out this issue [iPhone 5S Error](https://github.com/qiankanglai/ImagePicker/issues/2) here. I haven't found an elegant way to fix this, and any pull request is welcomed!

This utility lets you load images from device gallery and load it to your application as a Texture2D. You may draw Sprite with this texture or use it in other ways.

The origin project is https://github.com/Losiowaty/ImagePicker, and I clear the whole project, in addition to:

- add support for iPhone (combined with iPad)
- add support for Win32/OSX/Win8.1
- put Android support together
- take advantage of new cocos API
- Javascript Binding (lua binding to be done)

The image is loaded by platform API and deliveried to cocos in memory directly. No repeated IO is needed.

usage example screenshots: http://qiankanglai.me/project/2014/04/14/cocos2dx-ImagePicker/

Guide
=====
Installation
------------

Add the following sources into project according to different platforms (Files arranged with default cocos project folder structure). You need to add following files to xcodeproj/Android.mk/vcxproj.

- cocos2dx
    - extensions
        - ImagePicker
            - ImagePicker.h, ImagePicker.cpp, ImagePickerImpl.h (All Platform)
            - ImagePickerImpl.cpp (Android, Windows)
            - ImagePickerImpl.mm (iOS, OSX)
            - ImagePicker-ios.h, ImagePicker-ios.mm (iOS)
    - cocos
        - android
            - java
                - src
                    -org
                        -cocos2dx
                            - lib
                                - Cocos2dxImagePicker.java (Android)
        - scripting 
            - js-bindings
                - jsb_cocos2dx_extension_ImagePicker.h, jsb_cocos2dx_extension_ImagePicker.cpp (JS binding)
- proj.win8.1-universal
    - App.Shared
        - App.xaml.h, App.xaml.cpp (WP)

3. JSB

- jsb_cocos2dx_extension_ImagePicker.hpp
- jsb_cocos2dx_extension_ImagePicker.cpp

4. Tests (optional)

- ImagePickerTest.h, ImagePickerTest.cpp

5. Example Usage

- HelloWorldScene.h, HelloWorldScene.cpp

Usage
-----

Just call `ImagePicker::getInstance()->pickImage()` and pass in your delegate. If the image is picked successfully, your delegate will receive the corresponding Texture2D, or nullptr otherwise. An example usage could be found in HelloWorldScene.

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

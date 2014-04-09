ImagePicker
===========

ImagePicker utility for cocos2d-x 3.0 (Android and iOS).

This utility lets you load images from device gallery and load it to your application as a Texture2D. You may draw Sprite with this texture or use it in other ways.

The origin project is https://github.com/Losiowaty/ImagePicker, and I clear the whole project, in addition to:

- add support for iPhone (combined with iPad)
- take advantage of ccx 3.0 API

ps. The image is loaded by platform API and deliveried to ccx in memory directly. No repeated IO is needed.

Guide
=====
Installation
------------

1. iOS

Add the following sources into project:

- ImagePicker.h, ImagePicker.cpp
- ImagePickerImpl.h, ImagePickerImpl.mm
- ImagePickerIOS.h, ImagePickerIOS.mm

2. Android

- ImagePicker.h, ImagePicker.cpp
- ImagePickerImpl.h, ImagePickerImpl.cpp

Modify your `Cocos2dxActivity.java` file according to mine. You may just copy from line 50 to the bottom.

Usage
-----

Just call `ImagePicker::getInstance()->pickImage()` and pass in your delegate. If the image is picked successfully, your delegate will receive the corresponding Texture2D, or nullptr otherwise.
#ifndef __cocos2dx_ImagePicker_h__
#define __cocos2dx_ImagePicker_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_ImagePickerDelegate_class;
extern JSObject *jsb_cocos2d_ImagePickerDelegate_prototype;

bool js_cocos2dx_extension_ImagePickerDelegate_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ImagePickerDelegate_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ImagePickerDelegate(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_extension_ImagePicker(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_extension_ImagePickerDelegate_didFinishPickingWithResult(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ImagePickerDelegate_ImagePickerDelegate(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ImagePicker_class;
extern JSObject *jsb_cocos2d_ImagePicker_prototype;

bool js_cocos2dx_extension_ImagePicker_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ImagePicker_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ImagePicker(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_extension_ImagePicker(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_extension_ImagePicker_pickImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ImagePicker_finishImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ImagePicker_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ImagePicker_ImagePicker(JSContext *cx, uint32_t argc, jsval *vp);
#endif


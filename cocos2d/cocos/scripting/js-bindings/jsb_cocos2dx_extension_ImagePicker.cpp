#include "jsb_cocos2dx_extension_ImagePicker.hpp"
#include "cocos2d_specifics.hpp"
#include "extensions/ImagePicker/ImagePicker.h"

class JSBImagePickerDelegate : public cocos2d::ImagePickerDelegate {
public:
    JSBImagePickerDelegate()
    {};
    virtual void didFinishPickingWithResult(cocos2d::Texture2D* result)
    {
        js_proxy_t* p = jsb_get_native_proxy(this);
        jsval data;
        if(result == nullptr)
        {
            ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "didFinishPickingWithResult", 0, &data);
            return;
        }
        
        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Texture2D>(ScriptingCore::getInstance()->getGlobalContext(), result);
        data = OBJECT_TO_JSVAL(jsProxy->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "didFinishPickingWithResult", 1, &data);
    }
    virtual ~JSBImagePickerDelegate()
    {}
};

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.ref());
        JS::RootedObject parent(cx, typeClass->parentProto.ref());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_cocos2d_ImagePickerDelegate_class;
JSObject *jsb_cocos2d_ImagePickerDelegate_prototype;

bool js_cocos2dx_extension_ImagePickerDelegate_didFinishPickingWithResult(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JSBImagePickerDelegate* cobj = (JSBImagePickerDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ImagePickerDelegate_didFinishPickingWithResult : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Texture2D* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ImagePickerDelegate_didFinishPickingWithResult : Error processing arguments");
        cobj->didFinishPickingWithResult(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ImagePickerDelegate_didFinishPickingWithResult : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ImagePickerDelegate_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSBImagePickerDelegate* cobj = new (std::nothrow) JSBImagePickerDelegate();
    TypeTest<JSBImagePickerDelegate> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_cocos2d_ImagePickerDelegate_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ImagePickerDelegate)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        JSBImagePickerDelegate *nobj = static_cast<JSBImagePickerDelegate *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_cocos2dx_extension_ImagePickerDelegate(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ImagePickerDelegate_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ImagePickerDelegate_class->name = "ImagePickerDelegate";
    jsb_cocos2d_ImagePickerDelegate_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ImagePickerDelegate_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ImagePickerDelegate_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ImagePickerDelegate_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ImagePickerDelegate_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ImagePickerDelegate_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ImagePickerDelegate_class->convert = JS_ConvertStub;
    jsb_cocos2d_ImagePickerDelegate_class->finalize = js_cocos2d_ImagePickerDelegate_finalize;
    jsb_cocos2d_ImagePickerDelegate_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("didFinishPickingWithResult", js_cocos2dx_extension_ImagePickerDelegate_didFinishPickingWithResult, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_ImagePickerDelegate_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_ImagePickerDelegate_class,
        js_cocos2dx_extension_ImagePickerDelegate_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ImagePickerDelegate", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<JSBImagePickerDelegate> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ImagePickerDelegate_class;
        p->proto.ref() = jsb_cocos2d_ImagePickerDelegate_prototype;
        p->parentProto.ref() = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ImagePicker_class;
JSObject *jsb_cocos2d_ImagePicker_prototype;

bool js_cocos2dx_extension_ImagePicker_pickImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ImagePicker* cobj = (cocos2d::ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ImagePicker_pickImage : Invalid Native Object");
    if (argc == 1) {
        JSBImagePickerDelegate* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (JSBImagePickerDelegate*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ImagePicker_pickImage : Error processing arguments");
        cobj->pickImage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ImagePicker_pickImage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ImagePicker_finishImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ImagePicker* cobj = (cocos2d::ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ImagePicker_finishImage : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Texture2D* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ImagePicker_finishImage : Error processing arguments");
        cobj->finishImage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ImagePicker_finishImage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ImagePicker_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ImagePicker* ret = cocos2d::ImagePicker::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ImagePicker>(cx, (cocos2d::ImagePicker*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_ImagePicker_getInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_ImagePicker_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ImagePicker* cobj = new (std::nothrow) cocos2d::ImagePicker();
    TypeTest<cocos2d::ImagePicker> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_cocos2d_ImagePicker_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ImagePicker)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::ImagePicker *nobj = static_cast<cocos2d::ImagePicker *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_cocos2dx_extension_ImagePicker(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ImagePicker_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ImagePicker_class->name = "ImagePicker";
    jsb_cocos2d_ImagePicker_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ImagePicker_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ImagePicker_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ImagePicker_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ImagePicker_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ImagePicker_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ImagePicker_class->convert = JS_ConvertStub;
    jsb_cocos2d_ImagePicker_class->finalize = js_cocos2d_ImagePicker_finalize;
    jsb_cocos2d_ImagePicker_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("pickImage", js_cocos2dx_extension_ImagePicker_pickImage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("finishImage", js_cocos2dx_extension_ImagePicker_finishImage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_cocos2dx_extension_ImagePicker_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ImagePicker_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_ImagePicker_class,
        js_cocos2dx_extension_ImagePicker_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ImagePicker", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ImagePicker> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ImagePicker_class;
        p->proto.ref() = jsb_cocos2d_ImagePicker_prototype;
        p->parentProto.ref() = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_extension_ImagePicker(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_extension_ImagePickerDelegate(cx, ns);
    js_register_cocos2dx_extension_ImagePicker(cx, ns);
}


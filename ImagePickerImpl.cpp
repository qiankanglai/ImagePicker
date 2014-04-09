#include "cocos2d.h"

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "2d/platform/android/jni/JniHelper.h"

using namespace cocos2d;

extern "C" {
    void Java_org_cocos2dx_cpp_Cocos2dxActivity_ImagePickerResult(JNIEnv *env, jobject thiz, jbyteArray array)
    {
        jbyte* bufferPtr = env->GetByteArrayElements(array, NULL);
        jsize lengthOfArray = env->GetArrayLength(array);
        if(lengthOfArray > 1){
            Image *imf =new Image();
            imf->initWithImageData((unsigned char*)bufferPtr, lengthOfArray);
            imf->autorelease();
    
            Texture2D* pTexture = new Texture2D();
            pTexture->initWithImage(imf);

            ImagePicker::getInstance()->finishImage(pTexture);
        }
        else{
            ImagePicker::getInstance()->finishImage(nullptr);
        }
        env->ReleaseByteArrayElements(array, bufferPtr, 0);  
    }
}
#endif

void ImagePickerImpl::openImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/Cocos2dxActivity", "openImage", "()V");
    if (result)
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    else
        ImagePicker::getInstance()->finishImage(nullptr);
#else
    ImagePicker::getInstance()->finishImage(nullptr);
#endif
}

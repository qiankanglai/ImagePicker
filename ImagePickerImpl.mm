#include "cocos2d.h"

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ImagePickerIOS.h"
static ImagePickerIOS *sharedPicker = [[[ImagePickerIOS alloc] init] retain];
#endif

void ImagePickerImpl::openImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [sharedPicker takePicture];
#else
    ImagePicker::getInstance()->finishImage(nullptr);
#endif
}


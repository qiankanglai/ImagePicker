#include "App.xaml.h"
#include "OpenGLESPage.xaml.h"

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace cocos2d;
using namespace CocosAppWinRT;

App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
    Resuming += ref new EventHandler<Object^>(this, &App::OnResuming);
}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used when the application is launched to open a specific file, to display
/// search results, and so forth.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(LaunchActivatedEventArgs^ e)
{
    auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

    // Do not repeat app initialization when the Window already has content,
    // just ensure that the window is active.
    if (rootFrame == nullptr)
    {
        // Create a Frame to act as the navigation context and associate it with
        // a SuspensionManager key
        rootFrame = ref new Frame();

        // TODO: Change this value to a cache size that is appropriate for your application.
        rootFrame->CacheSize = 1;

        if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
        {
            // TODO: Restore the saved session state only when appropriate, scheduling the
            // final launch steps after the restore is complete.
        }

        // Place the frame in the current Window
        Window::Current->Content = rootFrame;
    }

    if (rootFrame->Content == nullptr)
    {
#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
        // Removes the turnstile navigation for startup.
        if (rootFrame->ContentTransitions != nullptr)
        {
            _transitions = ref new TransitionCollection();
            for (auto transition : rootFrame->ContentTransitions)
            {
                _transitions->Append(transition);
            }
        }

        rootFrame->ContentTransitions = nullptr;
        _firstNavigatedToken = rootFrame->Navigated += ref new NavigatedEventHandler(this, &App::RootFrame_FirstNavigated);
#endif

        // When the navigation stack isn't restored navigate to the first page,
        // configuring the new page by passing required information as a navigation
        // parameter.

        rootFrame->Content = mPage = ref new OpenGLESPage(&mOpenGLES);

#if 0
        if (!rootFrame->Navigate(OpenGLESPage::typeid, e->Arguments))
        {
            throw ref new FailureException("Failed to create initial page");
        }
#endif
    }

    // Ensure the current window is active
    Window::Current->Activate();
}

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
/// <summary>
/// Restores the content transitions after the app has launched.
/// </summary>
void App::RootFrame_FirstNavigated(Object^ sender, NavigationEventArgs^ e)
{
    auto rootFrame = safe_cast<Frame^>(sender);

    TransitionCollection^ newTransitions;
    if (_transitions == nullptr)
    {
        newTransitions = ref new TransitionCollection();
        newTransitions->Append(ref new NavigationThemeTransition());
    }
    else
    {
        newTransitions = _transitions;
    }

    rootFrame->ContentTransitions = newTransitions;

    rootFrame->Navigated -= _firstNavigatedToken;
}
#endif

/// <summary>
/// Invoked when application execution is being suspended. Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;	// Unused parameter
    (void) e;		// Unused parameter

     mPage->SetVisibility(false);
}

/// <summary>
/// Invoked when application execution is being resumed.
/// </summary>
/// <param name="sender">The source of the resume request.</param>
/// <param name="args">Details about the resume request.</param>
void App::OnResuming(Object ^sender, Object ^args)
{
    (void)sender; // Unused parameter
    (void)args; // Unused parameter

    mPage->SetVisibility(true);
}


#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#include "extensions/ImagePicker/ImagePicker.h"
#include <ppltasks.h>

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

void App::OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs ^ args)
{
    Application::OnActivated(args);
    if (args->Kind == Windows::ApplicationModel::Activation::ActivationKind::PickFileContinuation)
    {
        auto args2 = dynamic_cast<Windows::ApplicationModel::Activation::FileOpenPickerContinuationEventArgs^>(args);
        if (args2->Files == nullptr || args2->Files->Size == 0)
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
                ImagePicker::getInstance()->finishImage(nullptr);
            });
            return;
        }
        auto file = args2->Files->GetAt(0);
        auto dataReader = std::make_shared<DataReader^>(nullptr);
        create_task(file->OpenAsync(Windows::Storage::FileAccessMode::Read)).then([dataReader](Windows::Storage::Streams::IRandomAccessStream^ fileStream)
        {
            *dataReader = ref new DataReader(fileStream->GetInputStreamAt(0));
            return (*dataReader)->LoadAsync(fileStream->Size);
        }).then([dataReader](unsigned int bytes)
        {
            unsigned char* bufferPtr = new unsigned char[bytes];
            (*dataReader)->ReadBytes(ArrayReference<unsigned char>(bufferPtr, bytes));
            Image *image = new Image();
            image->initWithImageData((unsigned char*)bufferPtr, bytes);
            delete[] bufferPtr;

            Director::getInstance()->getScheduler()->performFunctionInCocosThread([image]{
                Texture2D* texture = new Texture2D();
                texture->initWithImage(image);
                texture->autorelease();
                image->release();

                ImagePicker::getInstance()->finishImage(texture);
            });
        });
    }
}
#endif
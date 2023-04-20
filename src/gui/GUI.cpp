#include "gui/GUI.h"

#include "core/BoardFile.hpp"

#include <iostream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

using namespace minesweeper;

Board _board;

GUI::GUI()
{
    Settings settings;

    settings.force_cpu_renderer = true;

    ///
    /// Create our main App instance.
    ///
    app_ = App::Create(settings);

    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    ///
    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                             false, kWindowFlags_Titled | kWindowFlags_Resizable);

    ///
    /// Create our HTML overlay-- we don't care about its initial size and
    /// position because it'll be calculated when we call OnResize() below.
    ///
    overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

    ///
    /// Force a call to OnResize to perform size/layout of our overlay.
    ///
    OnResize(window_.get(), window_->width(), window_->height());

    ///
    /// Load a page into our overlay's View
    ///
    overlay_->view()->LoadURL("file:///app.html");

    ///
    /// Register our GUI instance as an AppListener so we can handle the
    /// App's OnUpdate event below.
    ///
    app_->set_listener(this);

    ///
    /// Register our GUI instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our GUI instance as a LoadListener so we can handle the
    /// View's OnFinishLoading and OnDOMReady events below.
    ///
    overlay_->view()->set_load_listener(this);

    ///
    /// Register our GUI instance as a ViewListener so we can handle the
    /// View's OnChangeCursor and OnChangeTitle events below.
    ///
    overlay_->view()->set_view_listener(this);
}

GUI::~GUI()
{
}

void GUI::Run()
{
    app_->Run();
}

void GUI::OnUpdate()
{
    ///
    /// This is called repeatedly from the application's update loop.
    ///
    /// You should update any app logic here.
    ///
}

void GUI::OnClose(ultralight::Window *window)
{
    app_->Quit();
}

void GUI::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
    ///
    /// This is called whenever the window changes size (values in pixels).
    ///
    /// We resize our overlay here to take up the entire window.
    ///
    overlay_->Resize(width, height);
}

void GUI::OnFinishLoading(ultralight::View *caller,
                          uint64_t frame_id,
                          bool is_main_frame,
                          const String &url)
{
    ///
    /// This is called when a frame finishes loading on the page.
    ///
}

void GUI::OnDOMReady(ultralight::View *caller,
                     uint64_t frame_id,
                     bool is_main_frame,
                     const String &url)
{
    // Acquire the JS execution context for the current page.
    //
    // This call will lock the execution context for the current
    // thread as long as the Ref<> is alive.
    //
    RefPtr<JSContext> context = caller->LockJSContext();

    // Get the underlying JSContextRef for use with the
    // JavaScriptCore C API.
    JSContextRef ctx = context->ctx();

    // Get the global JavaScript object (aka 'window')
    JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

    // Create a JavaScript String containing the name of our callback.
    JSStringRef name_GetMessage = JSStringCreateWithUTF8CString("GetMessage");

    // Create a garbage-collected JavaScript function that is bound to our
    // native C callback 'GetMessage()'.
    JSObjectRef func_GetMessage =
        JSObjectMakeFunctionWithCallback(ctx, name_GetMessage, GUI::GetMessage);

    // Store our function in the page's global JavaScript object so that it
    // accessible from the page as 'OnButtonClick()'.
    JSObjectSetProperty(ctx, globalObj, name_GetMessage, func_GetMessage, 0, 0);

    /**
     * LoadBoard
     */
    JSStringRef name_LoadBoard = JSStringCreateWithUTF8CString("LoadBoard");

    JSObjectRef func_LoadBoard =
        JSObjectMakeFunctionWithCallback(ctx, name_LoadBoard, GUI::LoadBoard);

    JSObjectSetProperty(ctx, globalObj, name_LoadBoard, func_LoadBoard, 0, 0);

    // Release the JavaScript String we created earlier.
    JSStringRelease(name_GetMessage);
    JSStringRelease(name_LoadBoard);
}

void GUI::OnChangeCursor(ultralight::View *caller,
                         Cursor cursor)
{
    ///
    /// This is called whenever the page requests to change the cursor.
    ///
    /// We update the main window's cursor here.
    ///
    window_->SetCursor(cursor);
}

void GUI::OnChangeTitle(ultralight::View *caller,
                        const String &title)
{
    ///
    /// This is called whenever the page requests to change the title.
    ///
    /// We update the main window's title here.
    ///
    window_->SetTitle(title.utf8().data());
}

JSValueRef GUI::GetMessage(JSContextRef ctx, JSObjectRef function,
                           JSObjectRef thisObject, size_t argumentCount,
                           const JSValueRef arguments[],
                           JSValueRef *exception)
{

    ///
    /// Create a JavaScript String from a C-string, initialize it with our
    /// welcome message.
    ///
    JSStringRef str = JSStringCreateWithUTF8CString("Hello from C!");

    ///
    /// Create a garbage-collected JSValue using the String we just created.
    ///
    ///  **Note**:
    ///    Both JSValueRef and JSObjectRef types are garbage-collected types. (And actually,
    ///    JSObjectRef is just a typedef of JSValueRef, they share definitions).
    ///
    ///    The garbage collector in JavaScriptCore periodically scans the entire stack to check if
    ///    there are any active JSValueRefs, and marks those with no references for destruction.
    ///
    ///    If you happen to store a JSValueRef/JSObjectRef in heap memory or in memory unreachable
    ///    by the stack-based garbage-collector, you should explicitly call JSValueProtect() and
    ///    JSValueUnprotect() on the reference to ensure it is kept alive.
    ///
    JSValueRef value = JSValueMakeString(ctx, str);

    ///
    /// Release the string we created earlier (we only Release what we Create).
    ///
    JSStringRelease(str);

    return value;
}

JSValueRef GUI::LoadBoard(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[],
                          JSValueRef *exception)
{
    if ( argumentCount < 1 )
        return (JSValueRef)JSValueMakeBoolean(ctx, false);

    if ( !JSValueIsNumber(ctx, arguments[0]) )
        return (JSValueRef)JSValueMakeBoolean(ctx, false);

    int loadMode = int(JSValueToNumber(ctx, arguments[0], exception));

    bool success = false;

    switch ( loadMode )
    {
    case 0:
        if ( argumentCount < 2 )
        {
            success = false;
            break;
        }
        JSStringRef js_boardFilePath = JSValueToStringCopy(ctx, arguments[1],
                                                           exception);
        char boardFilePath[1024];
        JSStringGetUTF8CString(js_boardFilePath, boardFilePath, 1024);
        std::cout << boardFilePath << std::endl;
        BoardFile boardFile(boardFilePath);
        success = _board.loadBoardFile(boardFile);
        break;
    }

    JSValueRef r = JSValueMakeBoolean(ctx, success);

    return r;
}
/**
 *  File: GUI.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/04/22 20:39:44
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/26 11:54:13
 *  Description: GUI
 */

#include "gui/GUI.h"

#include "core/BoardFile.hpp"

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace minesweeper;

Board _board;

GUI::GUI()
{
    Settings settings;

    settings.force_cpu_renderer = false;

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

    /**
     * GetBoardWidth
     */
    JSStringRef name_GetBoardWidth = JSStringCreateWithUTF8CString("GetBoardWidth");

    JSObjectRef func_GetBoardWidth =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoardWidth, GUI::GetBoardWidth);

    JSObjectSetProperty(ctx, globalObj, name_GetBoardWidth, func_GetBoardWidth, 0, 0);

    /**
     * GetBoardHeight
     */
    JSStringRef name_GetBoardHeight = JSStringCreateWithUTF8CString("GetBoardHeight");

    JSObjectRef func_GetBoardHeight =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoardHeight, GUI::GetBoardHeight);

    JSObjectSetProperty(ctx, globalObj, name_GetBoardHeight, func_GetBoardHeight, 0, 0);

    /**
     * GetBoardGameState
     */
    JSStringRef name_GetBoardGameState = JSStringCreateWithUTF8CString("GetBoardGameState");

    JSObjectRef func_GetBoardGameState =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoardGameState, GUI::GetBoardGameState);

    JSObjectSetProperty(ctx, globalObj, name_GetBoardGameState, func_GetBoardGameState, 0, 0);

    /**
     * GetBoardWin
     */
    JSStringRef name_GetBoardWin = JSStringCreateWithUTF8CString("GetBoardWin");

    JSObjectRef func_GetBoardWin =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoardWin, GUI::GetBoardWin);

    JSObjectSetProperty(ctx, globalObj, name_GetBoardWin, func_GetBoardWin, 0, 0);

    /**
     * BoardStartGame
     */
    JSStringRef name_BoardStartGame = JSStringCreateWithUTF8CString("BoardStartGame");

    JSObjectRef func_BoardStartGame =
        JSObjectMakeFunctionWithCallback(ctx, name_BoardStartGame, GUI::BoardStartGame);

    JSObjectSetProperty(ctx, globalObj, name_BoardStartGame, func_BoardStartGame, 0, 0);

    /**
     * BoardReplay
     */
    JSStringRef name_BoardReplay = JSStringCreateWithUTF8CString("BoardReplay");

    JSObjectRef func_BoardReplay =
        JSObjectMakeFunctionWithCallback(ctx, name_BoardReplay, GUI::BoardReplay);

    JSObjectSetProperty(ctx, globalObj, name_BoardReplay, func_BoardReplay, 0, 0);

    /**
     * BoardAction
     */
    JSStringRef name_BoardAction = JSStringCreateWithUTF8CString("BoardAction");

    JSObjectRef func_BoardAction =
        JSObjectMakeFunctionWithCallback(ctx, name_BoardAction, GUI::BoardAction);

    JSObjectSetProperty(ctx, globalObj, name_BoardAction, func_BoardAction, 0, 0);

    /**
     * GetBoardFieldInChar
     */
    JSStringRef name_GetBoardFieldInChar = JSStringCreateWithUTF8CString("GetBoardFieldInChar");

    JSObjectRef func_GetBoardFieldInChar =
        JSObjectMakeFunctionWithCallback(ctx, name_GetBoardFieldInChar, GUI::GetBoardFieldInChar);

    JSObjectSetProperty(ctx, globalObj, name_GetBoardFieldInChar, func_GetBoardFieldInChar, 0, 0);

    // Release the JavaScript String we created earlier.
    JSStringRelease(name_GetMessage);
    JSStringRelease(name_LoadBoard);
    JSStringRelease(name_GetBoardWidth);
    JSStringRelease(name_GetBoardHeight);
    JSStringRelease(name_GetBoardGameState);
    JSStringRelease(name_GetBoardWin);
    JSStringRelease(name_BoardStartGame);
    JSStringRelease(name_BoardReplay);
    JSStringRelease(name_BoardAction);
    JSStringRelease(name_GetBoardFieldInChar);
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
    JSValueRef f = JSValueMakeBoolean(ctx, false);

    if ( argumentCount < 1 )
        return f;

    if ( !JSValueIsNumber(ctx, arguments[0]) )
        return f;

    int loadMode = int(JSValueToNumber(ctx, arguments[0], exception));

    bool success = false;

    if ( loadMode == 0 )
    {
        if ( argumentCount < 2 )
        {
            return f;
        }
        JSStringRef js_boardFilePath = JSValueToStringCopy(ctx, arguments[1],
                                                           exception);
        char boardFilePath[1024];
        JSStringGetUTF8CString(js_boardFilePath, boardFilePath, 1024);
        std::cout << "Load BoardFile " << boardFilePath << std::endl;
        BoardFile boardFile(boardFilePath);
        success = _board.loadBoardFile(boardFile);
    }
    else if ( loadMode == 1 )
    {
        if ( argumentCount < 4 )
        {
            return f;
        }
        int width = JSValueToNumber(ctx, arguments[1], exception);
        int height = JSValueToNumber(ctx, arguments[2], exception);
        int minesCount = JSValueToNumber(ctx, arguments[3], exception);
        std::cout << "Load RandomCount "
                  << width << " " << height << " " << minesCount << std::endl;
        _board.setSize(width, height);
        success = _board.randomMinesCount(minesCount);
    }
    else if ( loadMode == 2 )
    {
        if ( argumentCount < 4 )
        {
            return f;
        }
        int width = JSValueToNumber(ctx, arguments[1], exception);
        int height = JSValueToNumber(ctx, arguments[2], exception);
        double minesRate = JSValueToNumber(ctx, arguments[3], exception);
        std::cout << "Load RandomCount "
                  << width << " " << height << " " << minesRate << std::endl;
        _board.setSize(width, height);
        success = _board.randomMinesRate(minesRate);
    }

    if ( success )
        std::cout << "BoardAnswer=" << std::endl
                  << _board.getBoardWithoutCoverInString() << std::endl;

    JSValueRef r = JSValueMakeBoolean(ctx, success);

    return r;
}

JSValueRef GUI::GetBoardWidth(JSContextRef ctx, JSObjectRef function,
                              JSObjectRef thisObject, size_t argumentCount,
                              const JSValueRef arguments[],
                              JSValueRef *exception)
{
    size_t width = _board.w();

    JSValueRef r = JSValueMakeNumber(ctx, width);

    return r;
}

JSValueRef GUI::GetBoardHeight(JSContextRef ctx, JSObjectRef function,
                               JSObjectRef thisObject, size_t argumentCount,
                               const JSValueRef arguments[],
                               JSValueRef *exception)
{
    size_t height = _board.h();

    JSValueRef r = JSValueMakeNumber(ctx, height);

    return r;
}

JSValueRef GUI::GetBoardGameState(JSContextRef ctx, JSObjectRef function,
                                  JSObjectRef thisObject, size_t argumentCount,
                                  const JSValueRef arguments[],
                                  JSValueRef *exception)
{
    std::string state = _board.getStateInString();

    JSStringRef r_str = JSStringCreateWithUTF8CString(state.c_str());
    JSValueRef r = JSValueMakeString(ctx, r_str);
    JSStringRelease(r_str);

    return r;
}

JSValueRef GUI::GetBoardWin(JSContextRef ctx, JSObjectRef function,
                            JSObjectRef thisObject, size_t argumentCount,
                            const JSValueRef arguments[],
                            JSValueRef *exception)
{
    std::string win = _board.getWinInString();

    JSStringRef r_str = JSStringCreateWithUTF8CString(win.c_str());
    JSValueRef r = JSValueMakeString(ctx, r_str);
    JSStringRelease(r_str);

    return r;
}

JSValueRef GUI::BoardStartGame(JSContextRef ctx, JSObjectRef function,
                               JSObjectRef thisObject, size_t argumentCount,
                               const JSValueRef arguments[],
                               JSValueRef *exception)
{
    bool success = _board.start();

    JSValueRef r = JSValueMakeBoolean(ctx, success);

    return r;
}

JSValueRef GUI::BoardReplay(JSContextRef ctx, JSObjectRef function,
                            JSObjectRef thisObject, size_t argumentCount,
                            const JSValueRef arguments[],
                            JSValueRef *exception)
{
    _board.clear();

    JSValueRef r = JSValueMakeBoolean(ctx, true);

    return r;
}

JSValueRef GUI::BoardAction(JSContextRef ctx, JSObjectRef function,
                            JSObjectRef thisObject, size_t argumentCount,
                            const JSValueRef arguments[],
                            JSValueRef *exception)
{
    JSValueRef f = JSValueMakeBoolean(ctx, false);

    if ( argumentCount < 3 )
        return f;

    // x
    if ( !JSValueIsNumber(ctx, arguments[0]) )
        return f;

    // y
    if ( !JSValueIsNumber(ctx, arguments[1]) )
        return f;

    // right_click
    if ( !JSValueIsBoolean(ctx, arguments[2]) )
        return f;

    Pos pos;

    pos.x = JSValueToNumber(ctx, arguments[0], exception);
    pos.y = JSValueToNumber(ctx, arguments[1], exception);

    if ( !_board.inside(pos) )
        return f;

    bool right_click = JSValueToBoolean(ctx, arguments[2]);

    bool success = _board.action(pos, right_click);

    std::cout << "Board=" << std::endl
              << _board.getBoardInString() << std::endl;

    JSValueRef r = JSValueMakeBoolean(ctx, success);

    return r;
}

JSValueRef GUI::GetBoardFieldInChar(JSContextRef ctx, JSObjectRef function,
                                    JSObjectRef thisObject, size_t argumentCount,
                                    const JSValueRef arguments[],
                                    JSValueRef *exception)
{
    JSValueRef f = JSValueMakeNumber(ctx, '!');

    if ( argumentCount < 2 )
        return f;

    // x
    if ( !JSValueIsNumber(ctx, arguments[0]) )
        return f;

    // y
    if ( !JSValueIsNumber(ctx, arguments[1]) )
        return f;

    Pos pos;

    pos.x = JSValueToNumber(ctx, arguments[0], exception);
    pos.y = JSValueToNumber(ctx, arguments[1], exception);

    if ( !_board.inside(pos) )
        return f;

    char c = _board.getField(pos).getChar();

    JSValueRef r = JSValueMakeNumber(ctx, c);

    return r;
}
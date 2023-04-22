#pragma once

#include "core/Board.hpp"

#include <AppCore/AppCore.h>
#include <JavaScriptCore/JavaScript.h>

using namespace minesweeper;
using namespace ultralight;

class GUI : public AppListener,
            public WindowListener,
            public LoadListener,
            public ViewListener
{
public:
    GUI();

    virtual ~GUI();

    // Start the run loop.
    virtual void Run();

    // This is called continuously from the app's main loop.
    virtual void OnUpdate() override;

    // This is called when the window is closing.
    virtual void OnClose(ultralight::Window *window) override;

    // This is called whenever the window resizes.
    virtual void OnResize(ultralight::Window *window, uint32_t width,
                          uint32_t height) override;

    // This is called when the page finishes a load in one of its frames.
    virtual void OnFinishLoading(ultralight::View *caller,
                                 uint64_t frame_id,
                                 bool is_main_frame,
                                 const String &url) override;

    // This is called when the DOM has loaded in one of its frames.
    virtual void OnDOMReady(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url) override;

    // This is called when the page requests to change the Cursor.
    virtual void OnChangeCursor(ultralight::View *caller,
                                Cursor cursor) override;

    virtual void OnChangeTitle(ultralight::View *caller,
                               const String &title) override;

protected:
    RefPtr<App> app_;
    RefPtr<Window> window_;
    RefPtr<Overlay> overlay_;

private:
    static JSValueRef GetMessage(JSContextRef ctx, JSObjectRef function,
                                 JSObjectRef thisObject, size_t argumentCount,
                                 const JSValueRef arguments[],
                                 JSValueRef *exception);

    static JSValueRef LoadBoard(JSContextRef ctx, JSObjectRef function,
                                JSObjectRef thisObject, size_t argumentCount,
                                const JSValueRef arguments[],
                                JSValueRef *exception);

    static JSValueRef GetBoardWidth(JSContextRef ctx, JSObjectRef function,
                                    JSObjectRef thisObject, size_t argumentCount,
                                    const JSValueRef arguments[],
                                    JSValueRef *exception);

    static JSValueRef GetBoardHeight(JSContextRef ctx, JSObjectRef function,
                                     JSObjectRef thisObject, size_t argumentCount,
                                     const JSValueRef arguments[],
                                     JSValueRef *exception);

    static JSValueRef GetBoardGameState(JSContextRef ctx, JSObjectRef function,
                                        JSObjectRef thisObject, size_t argumentCount,
                                        const JSValueRef arguments[],
                                        JSValueRef *exception);

    static JSValueRef GetBoardWin(JSContextRef ctx, JSObjectRef function,
                                  JSObjectRef thisObject, size_t argumentCount,
                                  const JSValueRef arguments[],
                                  JSValueRef *exception);

    static JSValueRef BoardStartGame(JSContextRef ctx, JSObjectRef function,
                                     JSObjectRef thisObject, size_t argumentCount,
                                     const JSValueRef arguments[],
                                     JSValueRef *exception);

    static JSValueRef BoardReplay(JSContextRef ctx, JSObjectRef function,
                                  JSObjectRef thisObject, size_t argumentCount,
                                  const JSValueRef arguments[],
                                  JSValueRef *exception);

    static JSValueRef BoardAction(JSContextRef ctx, JSObjectRef function,
                                  JSObjectRef thisObject, size_t argumentCount,
                                  const JSValueRef arguments[],
                                  JSValueRef *exception);

    static JSValueRef GetBoardFieldInChar(JSContextRef ctx, JSObjectRef function,
                                          JSObjectRef thisObject, size_t argumentCount,
                                          const JSValueRef arguments[],
                                          JSValueRef *exception);
};

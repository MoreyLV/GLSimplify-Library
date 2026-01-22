//
// Created by Morey on 05/01/2026.
//

#ifndef GLSIMPLIFY_WINDOW_H
#define GLSIMPLIFY_WINDOW_H
#include <functional>
#include <string>
#include "ContextSettings.h"
#include "KeyTypes.h"

namespace gls{
    enum class Key;
    inline int window_width = 600;
    inline int window_height = 600;

    enum class EventType {
        Close,
        Resize,
        Key,
        Mouse
    };

    class Window {
    public:
        Window(int width, int height,const std::string& title, const ContextSettings& config);

        bool isOpen() const;
        void setVerticalSync(const bool& boolArgument) const;
        void update();
        void close() const;
        void resize(unsigned int width, unsigned int height) const;
        bool isKeyPressed(Key key) const;
        bool isKeyJustPressed(Key key) const;
        void clear(float r, float g, float b, float a);


    private:
        struct Impl;
        Impl* impl;

        static int activeWindowCheck(const Impl& impl);
        void pollEvent();

    };
};

#endif //GLSIMPLIFY_WINDOW_H
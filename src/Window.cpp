//
// Created by Morey on 05/01/2026.
//

#include "../include/gls/Window.h"
#include "glad/glad.h"
#include <iostream>
#include <SFML/Window.hpp>

#include "gls/Debug.h"


namespace gls {
    struct Window::Impl {
        sf::Window window;

        std::array<bool, 256> currentKeyState{};
        std::array<bool, 256> prevKeyState{};
        std::unordered_map<Key, bool> keyState;
        bool shouldCloseFlag = true;
    };

    Window::Window(
        int width,
        int height,
        const std::string& title,
        const ContextSettings& config
    )
    : impl(new Impl{}) {
        window_height = height;
        window_width = width;

        sf::ContextSettings contextSettings;

        contextSettings.depthBits = config.depthBits;
        contextSettings.stencilBits = config.stencilBits;
        contextSettings.antialiasingLevel = config.antialiasingLevel;
        contextSettings.majorVersion = config.majorVersion;
        contextSettings.minorVersion = config.minorVersion;

        if (config.flag == Core) contextSettings.attributeFlags = sf::ContextSettings::Core;

        impl->window.create(
            sf::VideoMode(width, height),
            title,
            sf::Style::Default,
            contextSettings
        );
        std::cout << "Window created" << std::endl;
        activeWindowCheck(*impl);
    }

    bool Window::isOpen() const {
        return impl->window.isOpen();
    }
    void Window::setVerticalSync(const bool& boolArgument) const {
        impl->window.setVerticalSyncEnabled(boolArgument);
        std::cout << "Window setVerticalSyncEnabled initialized as " << boolArgument << std::endl;
    }
    int Window::activeWindowCheck(const Impl& impl) {
        if (!impl.window.setActive(true)) {
            std::cerr << "Failed to activate OpenGL context" << std::endl;
            return -1;
        }
        std::cout << "Window activated" << std::endl;
        return 0;
    }

    static Key convertKey(sf::Keyboard::Key key) {
        switch (key) {
            case sf::Keyboard::Q:       return Key::Q;
            case sf::Keyboard::W:       return Key::W;
            case sf::Keyboard::E:       return Key::E;
            case sf::Keyboard::R:       return Key::R;
            case sf::Keyboard::T:       return Key::T;
            case sf::Keyboard::Y:       return Key::Y;
            case sf::Keyboard::U:       return Key::U;
            case sf::Keyboard::I:       return Key::I;
            case sf::Keyboard::O:       return Key::O;
            case sf::Keyboard::P:       return Key::P;
            case sf::Keyboard::A:       return Key::A;
            case sf::Keyboard::S:       return Key::S;
            case sf::Keyboard::D:       return Key::D;
            case sf::Keyboard::F:       return Key::F;
            case sf::Keyboard::G:       return Key::G;
            case sf::Keyboard::H:       return Key::H;
            case sf::Keyboard::J:       return Key::J;
            case sf::Keyboard::K:       return Key::K;
            case sf::Keyboard::L:       return Key::L;
            case sf::Keyboard::Z:       return Key::Z;
            case sf::Keyboard::X:       return Key::X;
            case sf::Keyboard::C:       return Key::C;
            case sf::Keyboard::V:       return Key::V;
            case sf::Keyboard::B:       return Key::B;
            case sf::Keyboard::N:       return Key::N;
            case sf::Keyboard::M:       return Key::M;
            default:                   return Key::Unknown;
        }
    }

    void Window::close() const {
        impl->window.close();
    }

    void Window::pollEvent() {
        sf::Event event{};
        while (impl->window.pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed) {
                Key key = convertKey(event.key.code);
                impl->currentKeyState[(int)key] = true;
            }

            if (event.type == sf::Event::KeyReleased) {
                Key key = convertKey(event.key.code);
                impl->currentKeyState[(int)key] = false;
            }

            if (event.type == sf::Event::Closed) {
                impl->shouldCloseFlag = true;
                impl->window.close();
            }
        }
    }
    bool Window::isKeyPressed(Key key) const {
        return impl->currentKeyState[(int)key];
    }

    bool Window::isKeyJustPressed(Key key) const {
        int k = (int)key;
        return impl->currentKeyState[k] && !impl->prevKeyState[k];
    }
    void Window::update(){
        impl->prevKeyState = impl->currentKeyState;

        pollEvent();
        impl->window.display();
    }
    void Window::resize(unsigned int width, unsigned int height) const {
        GL_CHECK(glViewport(0, 0, width, height));
        impl->window.setSize({width, height});
    }
    void Window::clear(float r, float g,float b, float a) {
        GL_CHECK(glClearColor(r, g, b, a));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
}

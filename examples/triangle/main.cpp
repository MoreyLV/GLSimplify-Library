//
// Created by Morey on 05/01/2026.
//

#include <iostream>
#include "random"
#include "../../include/gls/ContextSettings.h"
#include "../../include/gls/Window.h"
#include "gls/Mesh.h"
#include "gls/Render.h"
#include "gls/Shader.h"
#include "gls/VertexLayout.h"

int main() {

    gls::ContextSettings config = gls::ContextSettings(); // context setting are basic pre-sets fpr OpenGL defined in ContextSettings.h
    gls::Window window(900, 450, "Test Window", config); // window constructor requires (width, height, name, context settings) for window creation
    window.setVerticalSync(true); // vertical sync setting | True or False

    gls::Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag"); // your shaders (vertex and fragment) if you don't have any use default by /assets/shaders/basic.vert(frag)

    gls::VertexLayout layout;
    /* 1 layout is 1 preset for your shaders
       For example below:

       - if you have shaders requiring 2 arguments (vertex and color), you need to declare .add twice
       1st time is for vertex of size 3 (0.0f, 0.5f, 0.f // x,y,z)
       2nd time is for color after vertex with the same size 3 (1.0f, 0.0f, 0.0f // r,g,b)

       and full string looks like this in the end:
            mesh.upload({
                0.0f, 0.5f, 0.f,  1.0f, 0.0f, 0.0f
            },
                layout
            );

        if you wish to add 3rd argument for example "normal" for light calculation
        you need to add 3rd parameter to layout and final look will be like:

            layout.add(3, gls::AttrType::Float, false);
            layout.add(3, gls::AttrType::Float, false);
            layout.add(3, gls::AttrType::Float, false);

        and to mesh also:

            mesh.upload({ //upload function gets 1) vertices 2) indices 3) layout
                0.0f, 0.5f, 0.f,  1.0f, 0.0f, 0.0f,  2.0f, 3.0f, 1.0f
            },
            layout
            );

     */
    layout.add(3, gls::AttrType::Float, false); // (size, value_type (Int, Float, Uint))
    layout.add(3, gls::AttrType::Float, false);

    gls::Mesh mesh;
    gls::Render render;
    mesh.upload({ //upload function gets 1) vertices 2) indices 3) layout
        0.0f, 0.5f, 0.f,  1.0f, 0.0f, 0.0f, // x,y,z r,g,b
        -0.5f, -0.5f, 0.f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.f,  0.0f, 0.0f, 1.0f
    },
    {
        0, 1, 2 //optional argument, use it to explain to program how to connect your vertices right like 0 -> 1 -> 2
    },
    layout // connect your created previously layout
    );

    int exmpl_value = 0;
    float c_color = 100.f;

    while (window.isOpen()) { // main loop of window use it for rendering events

        window.update();
        if (window.isKeyPressed(gls::Key::Q)) { // right structure to use gls key bindings || THIS FUNCTION IS FOR MULTIPLY PRESS (FEW FRAMES)
            window.close(); // your event after key pressed
        }
        if (window.isKeyJustPressed(gls::Key::W)) { // || THIS FUNCTION IS FOR SINGLE PRESS (1 FRAME)
            std::cout << "JUST PRESSED\n";
            if (exmpl_value == 0) {
                c_color = 50.f/255.f;
                exmpl_value++;
            }
            else {
                c_color = 100.f/255.f;
                exmpl_value--;
            }
        }
        window.clear(c_color, c_color, c_color, 1.f); // fill window with specific color (r,g,b,a)
        render.draw(mesh, shader); // render your scene (mesh, shader)
    }

    return 0;
}

# GLSimplify

GLSimplify is a lightweight C++ wrapper library for OpenGL designed to simplify working with windows, shaders, meshes, and keyboard input.

The project is designed as a learning and practical library with a clean architecture and minimal API.

---

## ✨ Features

- Window and OpenGL context creation
- Input management (keyboard)
- Shader management (vertex / fragment)
- Mesh loading and rendering (VBO / optional EBO)
- Flexible Vertex Layout system
- Debug layer for OpenGL
- Simple architecture without overloaded abstractions

---

## 📦 Project Structure
GLSimplify/<br>
  include/gls/ # Library public API<br>
  src/ # Implementation<br>
    src/backends/ # Backend (SFML)<br>
  external/ # External dependencies (glad)<br>
  assets/shaders/ # Shader examples<br>
  examples/ # Usage Examples<br>
 CMakeLists.txt<br>

---

## 🛠 Dependencies

- **C++20**
- **OpenGL**
- **GLAD**
- **SFML** (used as a backend for the window and context)

All dependencies except SFML are already included in the repository.

---

## 🚀 Build

### Windows / Linux / macOS

git clone https://github.com/MoreyLV/GLSimplify-Library.git
cd GLSimplify-Library
mkdir build
cd build
cmake ..
cmake --build .

##▶ Usage Example
gls::Window window(900, 450, "GLSimplify");
gls::Shader shader("basic.vert", "basic.frag");

while (window.isOpen()) {
window.update();
window.clear(0.1f, 0.1f, 0.1f, 1.0f);
render.draw(mesh, shader);
}

The full example is available in examples/triangle.

##🎯 Project Goals

Simplify getting started with OpenGL

Create a clear architecture for learning

Gradually expand functionality (cameras, matrices, lighting, textures)

##📌 Project Status

Version: v0.1.0
The project is under active development.

##📜 License

The project is distributed under the MIT License.
See the LICENSE file for details.

##👤 Author

Morey
Junior C++ / Graphics / OpenGL Developer

GitHub: https://github.com/MoreyLV

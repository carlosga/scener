### SceneR - OpenGL 3D model renderer

#### C++ learning project.
The API is inspired on a subset of the Microsoft XNA 4 API.

* License.
    * [**MIT LICENSE**](http://opensource.org/licenses/MIT)
* Development platform.
    * **Linux**.
* C++ Compiler.
    * [**Clang**](http://clang.llvm.org/)
* C++ Standard Library.
    * [**libC++**](http://libcxx.llvm.org/)
* Third party dependencies.
    * [**OpenGL**](https://www.khronos.org/opengl/)
    * [**json11**](https://github.com/dropbox/json11)
    * [**GSL**](https://github.com/Microsoft/GSL)
    * [**nod**](https://github.com/fr00b0/nod)
    * [**Google Test**](https://code.google.com/p/googletest/)
* Asset format
    * [**glTF**](https://github.com/KhronosGroup/glTF)
* OpenGL loader
    * [**glad**](https://github.com/Dav1dde/glad)

## Build

### Linux (with clang)

#### Debug build:

  * cmake .. -DCMAKE_BUILD_TYPE=debug -DCMAKE_CXX_COMPILER=clang++-libc++ -DCMAKE_C_COMPILER=clang
  * make or make -jn

#### Release build:

  * cmake .. -DCMAKE_BUILD_TYPE=release -DCMAKE_CXX_COMPILER=clang++-libc++ -DCMAKE_C_COMPILER=clang
  * make or make -jn

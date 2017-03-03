# scener

OpenGL 3D model renderer (**C++ learning project**)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

| Name                                       | Version       |
|--------------------------------------------|---------------|
| C++ compiler                               | Clang 3.9     |
| C compiler                                 | Clang 3.9     |
| [**libC++**](http://libcxx.llvm.org/)      | 3.9 (Linux)   |

```
sudo apt-get install clang libc++ lldb git
```

### Compile from Source

A step by step series of examples that tell you have to get a development env running

1. Clone repository

```
git clone --recursive https://gitlab.com/carlosga/scener.git
```

2. Install dependencies (packages names for Debian)

```
sudo apt-get install cmake xorg-dev libgl1-mesa-dev
```

3. Configure the build (DEBUG)

```
cd scener
mkdir build\debug
cd build\debug
cmake ..\.. -DCMAKE_BUILD_TYPE=debug -DCMAKE_CXX_COMPILER=clang++-libc++ -DCMAKE_C_COMPILER=clang
```

4. Build 

```
make -j <NUM_CORES>
```

## Running the tests

```
make test
```

## Built With

| Name                                                        | Description          |
|-------------------------------------------------------------|----------------------|
| [**GSL**](https://github.com/Microsoft/GSL)                 |                      |
| [**JSON for Modern C++**](https://github.com/nlohmann/json) | JSON parser          |
| [**nod**](https://github.com/fr00b0/nod)                    | C++ signals library  |
| [**glad**](https://github.com/Dav1dde/glad)                 | OpenGL loader        |
| [**Google Test**](https://code.google.com/p/googletest/)    | Test framework       |
| [**glTF**](https://github.com/KhronosGroup/glTF)            | Asset format         |

## Authors

* **Carlos Guzmán Álvarez** - *Initial work* - [carlosga](https://gitlab.com/carlosga)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* The API is inspired on a subset of the Microsoft XNA 4 API
* Earthshaker model is a DOTA 2 model downloaded from [**DOTA 2 Workshop**](http://www.dota2.com/workshop/requirements),
  converted to COLLADA using [**Blender**](https://www.blender.org/) and finally to [**glTF**](https://github.com/KhronosGroup/glTF) 
  using the official COLLADA to glTF converter.
* The [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2) this README is based on

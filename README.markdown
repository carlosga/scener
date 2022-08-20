# scener

Vulkan 3D model renderer (**C++ learning project**)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

| Name          | Version       |
|---------------|---------------|
| C++ compiler  | Clang / GCC   |
| C compiler    | Clang / GCC   |

```
sudo apt-get install git cmake clang libc++ lldb
```

### Compile from Source

A step by step series of examples that tell you have to get a development env running

1. Clone repository

```
git clone --recurse-submodules https://github.com/carlosga/scener.git
```

2. Install dependencies (packages names for Debian)

```
sudo apt-get install xorg-dev libgl1-mesa-dev
```

3. Configure the build

3.1 (GCC - DEBUG)

```
cd scener
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

3.2 (CLANG - DEBUG)

```
cd scener
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
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

| Name                                                                                              | Description                          |
|---------------------------------------------------------------------------------------------------|--------------------------------------|
| [**Google Test**](https://code.google.com/p/googletest/)                                          | Test framework                       |
| [**GSL**](https://github.com/Microsoft/GSL)                                                       | Microsoft C++ GSL                    |
| [**JSON for Modern C++**](https://github.com/nlohmann/json)                                       | JSON parser                          |
| [**nod**](https://github.com/fr00b0/nod)                                                          | C++ signals library                  |
| [**Vulkan Memory Allocator**](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)  | AMD Vulkan Memory Allocation library |
| [**glTF**](https://github.com/KhronosGroup/glTF)                                                  | Asset format                         |

## Authors

* **Carlos Guzmán Álvarez** - *Initial work* - [carlosga](https://github.com/carlosga)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* The API is inspired on a subset of the Microsoft XNA 4 API
* Earthshaker model is a DOTA 2 model downloaded from [**DOTA 2 Workshop**](http://www.dota2.com/workshop/requirements),
  converted to COLLADA using [**Blender**](https://www.blender.org/) and finally to [**glTF**](https://github.com/KhronosGroup/glTF)
  using the official COLLADA to glTF converter.
* The [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2) this README is based on

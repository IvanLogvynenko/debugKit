# debugKit

Here is a simple library for code debugging in C++ 

# Usage

## Instalation

Download a `debugKit.cmake` file to your project directory and add
```cmake
install("debugKit.cmake")
```
to your *CMakeLists.txt* file and from now on every file in `include/` dir should be availible

To enable 
``` C++
LOG()
``` 
header, which provides basic logging, you would need to define `FULL_LOGGING` header by adding 
``` C++
#define FULL_LOGGING
```
or
```cmake
add_compile_definitions(FULL_LOGGING)
```
if you want to set it for all executables/libraries. 
If not then you can add it to a sertain executable/library by adding
```cmake
target_compile_definitions(<target-name> PUBLIC/PRIVATE FULL_LOGGING)
```
To set name for an executable to be something different from **Unnamed** you need to set a value for EXECUTABLE_NAME. It should be set by
```cmake
target_compile_definitions(<target-name> PRIVATE EXECUTABLE_NAME=<some-name>)
```
otherwise, if you have several targets for which you want different names, you would get an error.
``` C++
ILOG()
``` 
header, which provides logging of important events happend in your code, is enable by default. If you want to disable logging, you should define `RELEASE` header. 
To enable 
``` C++
EL()
``` 
header, which provides logging of errors that happen in your code, you would need to define `ERROR` header.
You can safely remove any of this headers, except for `RELEASE` if you want to create a release version without logging.
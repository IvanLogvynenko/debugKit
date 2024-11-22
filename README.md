# debugKit

Here is a simple library for code debugging in C++ 

# Usage

## Instalation

Download a `debugKit.cmake` file to your project directory and add
```cmake
install("debugKit.cmake")
```
to your *CMakeLists.txt* file

## Logger

This lib provides a logger class. Here is an example: 
```cpp
Logger logger = Logger();
logger << "some data to be written" << 42 << std::endl;
```
Notice: using std::endl won't affect performance since I'm handling it manualy. After logger recieves `std::endl` all data before(it is accumulated in the buffer) will be sent to the LoggerThread class that handles all logging. 
That means that if you pass "\n" your data won't be logged to the output stream right away. Of course all data from buffer is being sent to the logging service in the destructor but I don't think that it is intended behaviour.

### Levels 

There are following levels:
 - Critical
 - Debug
 - Error
 - Important
 - Info
 - Warning

The default level is Info, but can change it by passing any level in logger:
```cpp
Logger::debug
```

### Configuration

You can configure the logger with LoggerConfig.
`Important`: When LoggerThread get's started(it will happen after a logger dumps the buffer) it will skip all changes you make in the configuration, just because it doesn't like you. Enjoy, pull req will almost definitely be accepted

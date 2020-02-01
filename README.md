# cpp-async-timer
[![pipeline status](https://gitlab.com/ReimuNotMoe/cpp-async-timer/badges/master/pipeline.svg)](https://gitlab.com/ReimuNotMoe/cpp-async-timer/commits/master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/afc64343f5ac4395bc1c145dfab95684)](https://www.codacy.com/gh/YukiWorkshop/cpp-async-timer)
[![coverage report](https://gitlab.com/ReimuNotMoe/cpp-async-timer/badges/master/coverage.svg)](https://gitlab.com/ReimuNotMoe/cpp-async-timer/commits/master)

C++ async setInterval &amp; setTimeout implementation using Boost.

## Requirements
Reasonably new versions of:
-   C++17 compatible compiler
-   CMake
-   Boost

Quick command for Ubuntu users:
```shell script
apt install build-essential cmake libboost-all-dev
``` 

## Install
Use of Git submodule and CMake subdirectory is recommended.

```shell script
mkdir cpp_modules && cd cpp_modules
git submodule add https://github.com/YukiWorkshop/cpp-async-timer
```

This is a header-only library.

```cmake
include_directories(cpp_modules/cpp-async-timer)
target_link_libraries(your_project boost_system pthread)
```

## Usage
```cpp
#include <cpp-async-timer.hpp>

using namespace YukiWorkshop::AsyncTimer;
```

Print "aaaa" 5 times with an interval of one second:

```cpp
int cnt = 0;

TimerContext *t = setInterval(iosvc, [&](){
    puts("aaaa");
    cnt++;
    if (cnt == 5) clearInterval(t);
}, 1000);
```

Print "cccc" after 1.3 seconds:

```cpp
setTimeout(iosvc, [&](){
    puts("cccc");
}, 1300);
```

You won't see "dddd" after 1.4 seconds:

```cpp
TimerContext *t4 = setTimeout(iosvc, [&](){
    puts("dddd"); // You won't see this
}, 1400);

clearTimeout(t4);
```

Note: The timers will only start when `io_service` is running.

## License
MIT
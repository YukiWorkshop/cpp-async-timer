# cpp-async-timer
C++ async setInterval &amp; setTimeout implementation using Boost

## Usage
See `Test.cpp` for example.

```
#include "AsyncTimer.hpp"

using namespace YukiWorkshop::AsyncTimer;

TimerContext *setInterval(boost::asio::io_service &__io_svc, const std::function<void()> &__func, size_t __interval);
auto setTimeout(boost::asio::io_service &__io_svc, const std::function<void()> &__func, size_t __timeout);

void clearInterval(TimerContext *&__ctx);
void clearTimeout(TimerContext *&__ctx);
```

## License
MIT
#if defined(linux)
#include <libusbtc08-1.7/TC08Api.h>
#else
#include <usbtc08.h>
#endif

#include <cpp11.hpp>

int16_t units_(std::string x);

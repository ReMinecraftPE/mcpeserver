#pragma once
#include <climits>

// Have to do this because GCC on 64-bit targets makes longs 64-bit.
#if LONG_MAX != INT32_MAX
#define TLong int
#else
#define TLong long
#endif

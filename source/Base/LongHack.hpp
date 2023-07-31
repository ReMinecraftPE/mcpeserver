#pragma once
#include <climits>

// Have to do this because GCC on 64-bit targets makes longs 64-bit.
#if LONG_MAX != INT32_MAX
#define Long int
#else
#define Long long
#endif

/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

// note: not an official file name

#include "Utils.hpp"

#ifdef _WIN32
#include <Windows.h>

// Why are we not using GetTickCount64()? It's simple -- getTimeMs has the exact same problem as using regular old GetTickCount.
#pragma warning(disable : 28159)
#else
#include <sys/time.h>
#endif

int g_TimeSecondsOnInit = 0;

// In regular mode, getTimeMs depends on getTimeS.
// In Win32 mode, it's vice versa. Cool

int getTimeMs();

float getTimeS()
{
#ifdef _WIN32
	return float(getTimeMs()) / 1000.0f;
#else
	// variant implemented by Mojang. This does not work on MSVC
	timeval tv;
	gettimeofday(&tv, NULL);

	if (g_TimeSecondsOnInit == 0)
		g_TimeSecondsOnInit = tv.tv_sec;

	return float(tv.tv_sec - g_TimeSecondsOnInit) + float(tv.tv_usec) / 1000000.0f;
#endif
}

int getTimeMs()
{
#ifdef _WIN32
	// just return GetTickCount
	int time = GetTickCount();

	if (g_TimeSecondsOnInit == 0)
		g_TimeSecondsOnInit = time;

	return time - g_TimeSecondsOnInit;
#else
	return int(getTimeS() * 1000.0f);
#endif
}

time_t getRawTimeS()
{
#ifdef _WIN32
	return time_t(GetTickCount() / 1000);
#else
	timeval tv;
	gettimeofday(&tv, NULL);

	return tv.tv_sec;
#endif
}

time_t getEpochTimeS()
{
	return time(0);
}

float Max(float a, float b)
{
	if (a < b)
		a = b;
	return a;
}

void LogMsg(const char* fmt, ...)
{
	va_list lst;
	va_start(lst, fmt);
	vfprintf(stdout, fmt, lst);
	fprintf(stdout, "\n");
	va_end(lst);
}

// I hate duplicating code, but yeah
void LogMsgNoCR(const char* fmt, ...)
{
	va_list lst;
	va_start(lst, fmt);
	vfprintf(stdout, fmt, lst);
	va_end(lst);
}

void sleepMs(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(1000 * ms);
#endif
}

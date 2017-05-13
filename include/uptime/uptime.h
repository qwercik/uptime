#ifndef UPTIME_H
#define UPTIME_H

#include <stdint.h>

uint64_t getUptime(void);

#ifdef _WIN32
uint64_t getUptimeWindows(void);
#elif __linux__
uint64_t getUptimeLinux(void);
#endif

#endif
#include <uptime/uptime.h>

#ifdef _WIN32
#include <windows.h>
#elif linux
#include <stdio.h>
#else
#error Not supported platform
#endif


uint64_t getUptime(void)
{
#ifdef _WIN32
    return getUptimeWindows();
#elif __linux__
    return getUptimeLinux();
#endif
}

#ifdef _WIN32

uint64_t getUptimeWindows(void)
{
    return GetTickCount();
}

#elif __linux__

uint64_t getUptimeLinux(void)
{
    FILE* file = fopen("/proc/uptime", "r");

    if (file == NULL)
        return 0;

    uint64_t uptime;
    fscanf(file, "%d", &uptime);
    fclose(file);

    return uptime * 1000;
}

#endif


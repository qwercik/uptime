#include <uptime/uptime.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#elif __linux__ || __NetBSD__
#include <stdio.h>
#elif __FreeBSD__ || __APPLE__
#include <time.h>
#elif __OpenBSD__
#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>
#else
#error Not supported platform
#endif

#ifdef __APPLE__
#define GETTIME_OPTION CLOCK_MONOTONIC_RAW
#elif __FreeBSD__
#define GETTIME_OPTION CLOCK_UPTIME_PRECISE
#endif


#ifdef _WIN32
static uint64_t getUptimeWindows(void)
{
    return GetTickCount();
}

#elif __linux__ || __NetBSD__
static uint64_t getUptimeByUptimeFile(void)
{
    FILE* file = fopen("/proc/uptime", "r");

    if (file == NULL)
        return 0;

    double uptime;
    fscanf(file, "%lf", &uptime);
    fclose(file);

    return uptime * 1000;
}

#elif __FreeBSD__ || __APPLE__
static uint64_t getUptimeByClockGettime(void)
{
	struct timespec time_spec;

	if (clock_gettime(GETTIME_OPTION, &time_spec) != 0)
		return 0;

	uint64_t uptime = time_spec.tv_sec * 1000 + time_spec.tv_nsec / 1000000;
	return uptime;
}

#elif __OpenBSD__
static uint64_t getUptimeBySysctl(void)
{
	struct timeval time_val;
	size_t len = sizeof(time_val);
	int mib[2] = {CTL_KERN, KERN_BOOTTIME};

	if (sysctl(mib, 2, &time_val, &len, NULL, 0) != 0)
		return 0;

	uint64_t boottime = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
	uint64_t now = (uint64_t)time(NULL) * 1000;

	uint64_t uptime = now - boottime;
	return uptime;
}
#endif

uint64_t getUptime(void)
{
#ifdef _WIN32
    return getUptimeWindows();
#elif __linux__ || __NetBSD__
    return getUptimeByUptimeFile();
#elif __FreeBSD__ || __APPLE__
	return getUptimeByClockGettime();
#elif __OpenBSD__
	return getUptimeBySysctl();
#endif
}

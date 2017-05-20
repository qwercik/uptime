#include <uptime/uptime.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#elif linux
#include <stdio.h>
#elif __FreeBSD__
#include <time.h>
#elif __OpenBSD__
#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>
#else
#error Not supported platform
#endif

#ifdef _WIN32
uint64_t getUptimeWindows(void);
#elif __linux__
uint64_t getUptimeLinux(void);
#elif __FreeBSD__
uint64_t getUptimeFreeBSD(void);
#elif __OpenBSD__
uint64_t getUptimeOpenBSD(void);
#endif

uint64_t getUptime(void)
{
#ifdef _WIN32
    return getUptimeWindows();
#elif __linux__
    return getUptimeLinux();
#elif __FreeBSD__
	return getUptimeFreeBSD();
#elif __OpenBSD__
	return getUptimeOpenBSD();
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

#ifdef __FreeBSD__

uint64_t getUptimeFreeBSD(void)
{
	struct timespec time_spec;

	if (clock_gettime(CLOCK_UPTIME_PRECISE, &time_spec) != 0)
		return 0;

	uint64_t uptime = time_spec.tv_sec * 1000 + time_spec.tv_nsec / 1000000;
	return uptime;
}

#endif

#ifdef __OpenBSD__

uint64_t getUptimeOpenBSD(void)
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

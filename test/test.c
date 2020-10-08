#include <stdio.h>
#include <uptime/uptime.h>

int main(void)
{
    printf("Uptime: %lu\n", getUptime());
}

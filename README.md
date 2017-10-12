# Uptime

## Description
Uptime is a simple cross-platform library for C/C++, that lets you get operating system uptime.

## Supported Platforms
- Linux
- Windows
- FreeBSD
- OpenBSD
- NetBSD
- macOS

## Installation
First you must compile library from sources or use an existing library binary file. You can use CMakeLists.txt script, which you are able to find in this repository.

Then, you can move a content of *uptime/include* and *uptime/lib* directories to your compiler's and linker's default directories. Otherwise, you will have to add to your projects custom paths with header and library files.

## Usage

```c
// File: example.c
#include <stdio.h>
#include <uptime/uptime.h>
int main(void)
{
    printf("System uptime: %d", getUptime());
}

```

Function *getUptime()* takes no arguments and returns an **uint64_t** value - operating system uptime measured in milliseconds.

If you want to compile your project, you have to link the library. An example (using GCC):

```bash
$ gcc -o example example.c -luptime
```

If you haven't installed the library to defaults locations, you have to indicate your custom header and library paths. Example:
 
```bash
$ gcc -o example example.c -L/home/user/uptime/lib -I/home/user/uptime/include -luptime
```


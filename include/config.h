#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifdef _WIN32
#include <Windows.h>
#define delay(x)   ::Sleep(x)
#else
#include <unistd.h>
static inline void delay(__int32_t ms){      // _word_size_t ms
    while (ms>=1000){
        usleep(1000*1000);
        ms-=1000;
    };
    if (ms!=0)
        usleep(ms*1000);
}
#endif

typedef struct {
    double  dst;
    double  angle;
    int32_t quality;
    bool    is_start;

} __scandot;

#endif // CONFIG_H

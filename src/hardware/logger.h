#pragma once

#include <Arduino.h>

class Logger {
public:
    static void init();
    static void print(const char* message);
    static void println(const char* message);
    static void printf(const char* format, ...);
};

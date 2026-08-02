#include "logger.h"

void Logger::init() {
    Serial.begin(115200);
}

void Logger::print(const char* message) {
    Serial.print(message);
}

void Logger::println(const char* message) {
    Serial.println(message);
}

void Logger::printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    Serial.print(buffer);
}

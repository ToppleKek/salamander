#ifndef SALAMANDER_LOGGER_H
#define SALAMANDER_LOGGER_H

#include <string>
#include <iostream>
#include <ctime>
#include <fmt/core.h>

namespace Logger {
    static std::string timestr() noexcept {
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[9];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 9, "%H:%M:%S", timeinfo);
        return std::string(buffer);
    }

    template<typename... Args>
    static void info(const std::string &fmt, Args... args) {
        std::string str = "[" + timestr() + "] INFO: " + fmt + "\n";
        fmt::print(str, args...);
    }

    template<typename... Args>
    static void warn(const std::string &fmt, Args... args) {
        std::string str = "[" + timestr() + "] WARN: " + fmt + "\n";
        fmt::print(str, args...);
    }

    template<typename... Args>
    static void error(const std::string &fmt, Args... args) {
        std::string str = "[" + timestr() + "] ERROR: " + fmt + "\n";
        fmt::print(str, args...);
    }
}



#endif //SALAMANDER_LOGGER_H

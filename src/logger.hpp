#pragma once
#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "utils.h"

#define SPACE_SIZE 10

enum class Level {
    DEBUG,
    INFO,
    ERROR,
    TRACE
};

enum class Output {
    STDOUT,
    FILE,
    NONE
};


class Logger
{
public:
    Logger();
    Logger(const char *space);

    // template <typename

    template <typename Type>
    Logger& operator << (Type text)
    {
        write(0, text, strlen(text));
        return *this;
    }

    Logger& operator << (u8 ch)
    {
        char text[4];
        itoa(ch, text, 10);
        write(0, text, strlen(text));
        return *this;
    }
    
    Logger& operator << (u32 ch)
    {
        char text[40];
        itoa(ch, text, 10);
        write(0, text, strlen(text));
        return *this;
    }

    Logger& operator << (char ch)
    {
        char text[1];
        text[0] = ch;
        write(0, text, strlen(text));
        return *this;
    }

    Logger& operator << (int ch)
    {
        char text[20];
        itoa(ch, text, 10);
        write(0, text, strlen(text));
        return *this;
    }

    Logger& operator << (const Level& level)
    {
        write(0, "<", 1);
        const char* time = getTimeString();
        write(0, time, strlen(time));
        write(0, "> ", 2);
        write(0, getLevelString(level), strlen(getLevelString(level)));
        write(0, "/", 1);
        write(0, name_, strlen(name_));
        write(0, ": ", 2);
        return *this;
    }

    char name_[SPACE_SIZE];
private:
    const char* getLevelString(const Level& level);
    const char *getTimeString();
};
#pragma once

#ifndef LOGGINGLIB_H
#define LOGGINGLIB_H

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>


// * Logging
#define __LOGGING_TRACE "[ ]"
#define __LOGGING_DEBUG "[:]"
#define __LOGGING_INFO "[$]"
#define __LOGGING_WARNING "[*]"
#define __LOGGING_ERROR "[!]"
#define __LOGGING_FATAL "[X]"

#define __LOGGING_TRACE_COLOR "\033[0m"
#define __LOGGING_DEBUG_COLOR "\033[0;36m"
#define __LOGGING_INFO_COLOR "\033[0;32m"
#define __LOGGING_WARNING_COLOR "\033[0;33m"
#define __LOGGING_ERROR_COLOR "\033[0;31m"
#define __LOGGING_FATAL_COLOR "\033[0;35m"


// * Main Debugging
static const bool __MAIN_DEBUG = true;
#define __MAIN_LOGID "[Main]"

// * Object Engine Debugging
static const bool __OE_DEBUG = true;
#define __OE_LOGID "[Object Engine]"


// * Logging table
const std::unordered_map<std::string, const bool> __LOGGING_TABLE = {
    {__MAIN_LOGID, __MAIN_DEBUG},
    {__OE_LOGID, __OE_DEBUG},
}; 

const std::unordered_map<std::string, const int> __LOGGING_LEVELS = {
    {__LOGGING_TRACE, 0},
    {__LOGGING_DEBUG, 1},
    {__LOGGING_INFO, 2},
    {__LOGGING_WARNING, 3},
    {__LOGGING_ERROR, 4},
    {__LOGGING_FATAL, 5},
};


// * Extern Variables
extern const char* __LOGGING_LEVEL;

// * Extern Functions
template <typename Type>
void logMessage(const Type& message, const std::string& level, const std::string& id) {
    std::ostringstream oStringStream;
    oStringStream << message;
    std::string stringMessage = oStringStream.str();

    if (!__LOGGING_TABLE.at(id)) {
        return;
    }
    if (__LOGGING_LEVELS.at(level) < __LOGGING_LEVELS.at(__LOGGING_LEVEL)) {
        return;
    }

    std::cout << level << " " << id << " " << stringMessage << std::endl;
}

extern "C" {}

#endif

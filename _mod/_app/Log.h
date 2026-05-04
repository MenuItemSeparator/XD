// Asynchronous logger that writes logs to a file without blocking the main thread.
// Supports different logging levels (info, warning, error) and configurable output format.
#pragma once

#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <sstream>
#include "Result.h"

namespace XD{

enum class LogLevel {
    Info = 0,
    Warning = 1,
    Error = 2
};

class Log
{
public:
    Log();
    ~Log();

    Result fn_Run(const std::string& _filePath);
    Result fn_Log(const std::string& _message, LogLevel _level, int _code);
    Result fn_Stop();
    Result fn_ClearFile();
    Result fn_GetError();
    Result fn_ClearErrors();

private:
    bool Var_IsRunning;
    std::thread Var_LoggerThread;
    std::queue<std::string> Var_LogQueue;
    std::mutex Var_QueueMutex;
    std::vector<std::string> Var_Errors;
    std::string Var_FilePath;
};

}
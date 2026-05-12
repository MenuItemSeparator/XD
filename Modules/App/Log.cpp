#include "Log.h"
#include <fstream>
#include <chrono>
#include <iomanip>

namespace nXD {

Log::Log() : Var_IsRunning(false) {
}

Log::~Log() {
    if (Var_IsRunning) {
        fn_Stop();
    }
}

Result 
Log::fn_Run(const std::string& _filePath) {
    if (Var_IsRunning) {
        Result result;
        result.fn_SetStatus((int)ResultStatus::Warning);
        return result;
    }

    Var_FilePath = _filePath;
    Var_IsRunning = true;

    // Start logging thread
    Var_LoggerThread = std::thread([this]() {
        std::ofstream logFile(Var_FilePath, std::ios::app);
        if (!logFile.is_open()) {
            return;
        }

        while (Var_IsRunning) {
            {
                std::lock_guard<std::mutex> lock(Var_QueueMutex);
                while (!Var_LogQueue.empty()) {
                    logFile << Var_LogQueue.front();
                    Var_LogQueue.pop();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        logFile.close();
    });

    Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

Result 
Log::fn_Log(const std::string& _message, LogLevel _level, int _code) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] ";

    switch (_level) {
        case LogLevel::Info:
            oss << "[INFO] ";
            break;
        case LogLevel::Warning:
            oss << "[WARNING] ";
            break;
        case LogLevel::Error:
            oss << "[ERROR] ";
            break;
    }

    oss << "Code: " << _code << " | " << _message << "\n";

    {
        std::lock_guard<std::mutex> lock(Var_QueueMutex);
        Var_LogQueue.push(oss.str());
    }

    Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

Result 
Log::fn_Stop() {
    Var_IsRunning = false;

    if (Var_LoggerThread.joinable()) {
        Var_LoggerThread.join();
    }

    Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

Result 
Log::fn_ClearFile() {
    std::ofstream logFile(Var_FilePath, std::ios::trunc);
    logFile.close();

    Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

Result 
Log::fn_GetError() {
    Result result;
    if (Var_Errors.empty()) {
        result.fn_SetStatus((int)ResultStatus::Warning);
    } else {
        result.fn_SetStatus((int)ResultStatus::Error);
    }
    return result;
}

Result 
Log::fn_ClearErrors() {
    Var_Errors.clear();

    Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

} // namespace nXD

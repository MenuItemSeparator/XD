#include "App.h"
#include "Result.h"

namespace XD {

App::App() : Var_IsInitialized(false), Var_IsRunning(false) {
}

App::~App() {
    if (Var_IsRunning) {
        fn_Stop();
    }
}

XD::Result App::fn_Init() {
    if (Var_IsInitialized) {
        XD::Result result;
        result.fn_SetStatus((int)ResultStatus::Warning);
        result.fn_AddErrorMessage("Application already initialized");
        return result;
    }

    // Initialize subsystems here
    Var_IsInitialized = true;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result App::fn_Run() {
    if (!Var_IsInitialized) {
        XD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        result.fn_AddErrorMessage("Application not initialized");
        return result;
    }

    Var_IsRunning = true;

    // Main application loop here
    while (Var_IsRunning) {
        // Process events, update, render
    }

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result App::fn_Stop() {
    Var_IsRunning = false;

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

} // namespace XD

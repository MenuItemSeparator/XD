#include "App.h"
#include "Result.h"

namespace nXD {

App::App() : Var_IsInitialized(false), Var_IsRunning(false) {
}

App::~App() {
    if (Var_IsRunning) {
        fn_Stop();
    }
}

nXD::Result 
App::fn_Init() {
    if (Var_IsInitialized) {
        nXD::Result result;
        result.fn_SetStatus((int)ResultStatus::Warning);
        return result;
    }

    // Initialize subsystems here
    Var_IsInitialized = true;

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result
App::fn_Run() {
    if (!Var_IsInitialized) {
        nXD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        return result;
    }

    Var_IsRunning = true;

    // Main application loop here
    while (Var_IsRunning) {
        // Process events, update, render
    }

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result 
App::fn_Stop() {
    Var_IsRunning = false;

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

} // namespace nXD

// Result management class for operation status, error messages, and associated data.
// Debug mode controls error handling and throws exceptions if errors are unprocessed.
// Error codes: < 0 = error, 0 = warning, > 0 = success
#pragma once

#include <csignal>

namespace nXD{

enum ResultStatus : int_fast32_t
{
    Error = -1,
    Warning = 0,
    Success = 1
};

void DebugBreak(const char _Message[])
{
//    __asm__("int $3");
//    std::raise(SIGTRAP);
}

class Result
{
    public:
        Result() {}
        Result(int _Status) : Var_Status(_Status) {}
        Result(ResultStatus _Status) : Var_Status(static_cast<int>(_Status)) {}
        ~Result()
        {
            if(Var_Status < 0)
            {

            }
        }

        void fn_SetStatus(int _Status) {Var_Status = _Status;}
        int fn_GetStatus() const { return Var_Status; }

        void fn_Clear() { Var_Status = 0; }

        // Operators for comparison
        bool operator==(int _Status) const { return Var_Status == _Status; }
        bool operator!=(int _Status) const { return Var_Status != _Status; }
        bool operator==(ResultStatus _Status) const {  return Var_Status == _Status; }
        bool operator!=(ResultStatus _Status) const {  return Var_Status != _Status; }
        operator int() const { return Var_Status; }

    private:
        int Var_Status;
};
}
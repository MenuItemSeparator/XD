// Result management class for operation status, error messages, and associated data.
// Debug mode controls error handling and throws exceptions if errors are unprocessed.
// Error codes: < 0 = error, 0 = warning, > 0 = success
#pragma once

namespace XD{

enum class ResultStatus {
    Error = -1,
    Warning = 0,
    Success = 1
};

class Result
{
    public:
        Result();
        Result(int _status);
        ~Result();

        void fn_SetStatus(int _status);
        int fn_GetStatus() const;

        void fn_SetData(void* _data);
        void* fn_GetData() const;

        void fn_Clear();

        // Operators for comparison
        bool operator==(int _status) const;
        bool operator!=(int _status) const;
        bool operator==(ResultStatus _status) const;
        bool operator!=(ResultStatus _status) const;
        operator int() const;

    private:
        int Var_Status;
        void* Var_Data;
};
}
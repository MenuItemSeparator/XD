#include "Result.h"

namespace nXD {

Result::Result() : Var_Status((int)ResultStatus::Success), Var_Data(nullptr) {
}

Result::Result(int _status) : Var_Status(_status), Var_Data(nullptr) {
}

Result::~Result() {
    Var_Data = nullptr;
}

void 
Result::fn_SetStatus(int _status) {
    Var_Status = _status;
}

int 
Result::fn_GetStatus() const {
    return Var_Status;
}

void 
Result::fn_SetData(void* _data) {
    Var_Data = _data;
}

void* 
Result::fn_GetData() const {
    return Var_Data;
}

void 
Result::fn_Clear() {
    Var_Status = (int)ResultStatus::Success;
    Var_Data = nullptr;
}

bool 
Result::operator==(int _status) const {
    return Var_Status == _status;
}

bool 
Result::operator!=(int _status) const {
    return Var_Status != _status;
}

bool 
Result::operator==(ResultStatus _status) const {
    return Var_Status == (int)_status;
}

bool 
Result::operator!=(ResultStatus _status) const {
    return Var_Status != (int)_status;
}

Result::operator int() const {
    return Var_Status;
}

} // namespace nXD

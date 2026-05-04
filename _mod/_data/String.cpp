#include "String.h"
#include "../_app/Result.h"
#include <cctype>
#include <cstring>

namespace XD {

String::String() : Var_Length(0) {
    Var_Data[0] = '\0';
}

String::String(const char* _str) {
    if (_str == nullptr) {
        Var_Length = 0;
        Var_Data[0] = '\0';
    } else {
        Var_Length = strlen(_str);
        if (Var_Length >= MAX_LENGTH) {
            Var_Length = MAX_LENGTH - 1;
        }
        strncpy(Var_Data, _str, Var_Length);
        Var_Data[Var_Length] = '\0';
    }
}

String::String(const String& _other) : Var_Length(_other.Var_Length) {
    strncpy(Var_Data, _other.Var_Data, Var_Length);
    Var_Data[Var_Length] = '\0';
}

String::~String() {
    Var_Length = 0;
}

String& String::operator=(const String& _other) {
    if (this != &_other) {
        Var_Length = _other.Var_Length;
        strncpy(Var_Data, _other.Var_Data, Var_Length);
        Var_Data[Var_Length] = '\0';
    }
    return *this;
}

bool String::operator==(const String& _other) const {
    return strcmp(Var_Data, _other.Var_Data) == 0;
}

bool String::operator!=(const String& _other) const {
    return strcmp(Var_Data, _other.Var_Data) != 0;
}

XD::Result String::fn_Concat(const String& _str) {
    size_t newLength = Var_Length + _str.Var_Length;
    
    if (newLength >= MAX_LENGTH) {
        XD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        result.fn_AddErrorMessage("String concatenation would exceed max length");
        return result;
    }

    strncat(Var_Data, _str.Var_Data, _str.Var_Length);
    Var_Length = newLength;
    Var_Data[Var_Length] = '\0';

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

int String::fn_Find(const String& _substr) const {
    const char* pos = strstr(Var_Data, _substr.Var_Data);
    if (pos == nullptr) {
        return -1;
    }
    return (int)(pos - Var_Data);
}

XD::Result String::fn_Replace(char _oldChar, char _newChar) {
    for (size_t i = 0; i < Var_Length; ++i) {
        if (Var_Data[i] == _oldChar) {
            Var_Data[i] = _newChar;
        }
    }

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result String::fn_ToUpper() {
    for (size_t i = 0; i < Var_Length; ++i) {
        Var_Data[i] = std::toupper((unsigned char)Var_Data[i]);
    }

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

XD::Result String::fn_ToLower() {
    for (size_t i = 0; i < Var_Length; ++i) {
        Var_Data[i] = std::tolower((unsigned char)Var_Data[i]);
    }

    XD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

size_t String::fn_Length() const {
    return Var_Length;
}

char String::fn_CharAt(int _index) const {
    if (_index < 0 || _index >= (int)Var_Length) {
        return '\0';
    }
    return Var_Data[_index];
}

bool String::fn_Equals(const String& _str) const {
    return strcmp(Var_Data, _str.Var_Data) == 0;
}

const char* String::fn_CStr() const {
    return Var_Data;
}

} // namespace XD

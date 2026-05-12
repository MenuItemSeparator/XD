// Simplified string class providing basic string operations optimized for performance.
// Stack-based allocation without dynamic memory, with efficient resource management.
#pragma once

#include <string>
#include <cstring>

namespace nXD{

class String
{
public:
    String();
    String(const char* _str);
    String(const String& _other);
    ~String();

    String& operator=(const String& _other);
    bool operator==(const String& _other) const;
    bool operator!=(const String& _other) const;

    nXD::Result fn_Concat(const String& _str);
    int fn_Find(const String& _substr) const;
    nXD::Result fn_Replace(char _oldChar, char _newChar);
    nXD::Result fn_ToUpper();
    nXD::Result fn_ToLower();
    size_t fn_Length() const;
    char fn_CharAt(int _index) const;
    bool fn_Equals(const String& _str) const;
    const char* fn_CStr() const;

private:
    static const size_t MAX_LENGTH = 256;
    char Var_Data[MAX_LENGTH];
    size_t Var_Length;
};

}
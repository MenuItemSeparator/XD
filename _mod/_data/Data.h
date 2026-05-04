// Data management class for handling loading, saving, and processing application data.
// Supports various data formats (JSON, XML) with serialization/deserialization capabilities.
#pragma once

#include <string>
#include <map>
#include <memory>
#include "../_app/Result.h"

namespace XD{

class Data
{
public:
    Data();
    ~Data();

    XD::Result fn_LoadData(const std::string& _filePath);
    XD::Result fn_SaveData(const std::string& _filePath);
    XD::Result fn_ProcessData();
    void* fn_GetData() const;
    XD::Result fn_ClearData();

private:
    std::map<std::string, void*> Var_DataMap;
    bool Var_IsLoaded;
    bool Var_IsModified;
};

}
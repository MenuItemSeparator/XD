// Data management class for handling loading, saving, and processing application data.
// Supports various data formats (JSON, XML) with serialization/deserialization capabilities.
#pragma once

#include <string>
#include <map>
#include <memory>
#include "../_app/Result.h"

namespace nXD{

class Data
{
public:
    Data();
    ~Data();

    nXD::Result fn_LoadData(const std::string& _filePath);
    nXD::Result fn_SaveData(const std::string& _filePath);
    nXD::Result fn_ProcessData();
    void* fn_GetData() const;
    nXD::Result fn_ClearData();

private:
    std::map<std::string, void*> Var_DataMap;
    bool Var_IsLoaded;
    bool Var_IsModified;
};

}
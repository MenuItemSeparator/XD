#include "Data.h"

namespace nXD {

Data::Data() : Var_IsLoaded(false), Var_IsModified(false) {
}

Data::~Data() {
    fn_ClearData();
}

nXD::Result 
Data::fn_LoadData(const std::string& _filePath) {
    // TODO: Implement actual data loading from file
    // For now, just mark as loaded
    Var_IsLoaded = true;
    Var_IsModified = false;

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result 
Data::fn_SaveData(const std::string& _filePath) {
    if (!Var_IsLoaded) {
    nXD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        return result;
    }

    // TODO: Implement actual data saving to file
    Var_IsModified = false;

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

nXD::Result 
Data::fn_ProcessData() 
{
    if (!Var_IsLoaded) 
    {
        nXD::Result result;
        result.fn_SetStatus((int)ResultStatus::Error);
        return result;
    }

    // TODO: Implement data processing logic
    Var_IsModified = true;

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

void* 
Data::fn_GetData() const 
{
    // Return pointer to data map for now
    return (void*)&Var_DataMap;
}

nXD::Result 
Data::fn_ClearData() 
{
    for (auto& pair : Var_DataMap) {
        if (pair.second != nullptr) {
            // TODO: Implement proper cleanup based on data type
        }
    }
    Var_DataMap.clear();
    Var_IsLoaded = false;
    Var_IsModified = false;

    nXD::Result result;
    result.fn_SetStatus((int)ResultStatus::Success);
    return result;
}

} // namespace nXD

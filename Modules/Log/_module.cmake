set(ModuleName Log)

#Includes
set(Module${ModuleName}_Includes ${XD_ROOT_PATH}/Modules/Log/)

#Sources
set(Module${ModuleName}_Sources 
    ${XD_ROOT_PATH}/Modules/Log/Log.cpp
    ${XD_ROOT_PATH}/Modules/Log/Log.h
)

message(============Module Info=============)
message("Module Name : ${ModuleName}")
message("Module Includes : ${Module${ModuleName}_Includes}")
message("Module Sources : ${Module${ModuleName}_Sources}")
message(====================================)
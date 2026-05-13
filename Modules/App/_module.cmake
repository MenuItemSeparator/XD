set(ModuleName App)

#Includes
set(Module${ModuleName}_Includes ${XD_ROOT_PATH}/Modules/App/)

#Sources
set(Module${ModuleName}_Sources 
    ${XD_ROOT_PATH}/Modules/App/App.cpp
    ${XD_ROOT_PATH}/Modules/App/App.h
    ${XD_ROOT_PATH}/Modules/App/Result.cpp
    ${XD_ROOT_PATH}/Modules/App/Result.h
    ${XD_ROOT_PATH}/Modules/App/Log.h
    ${XD_ROOT_PATH}/Modules/App/Log.cpp
)

message(============Module Info=============)
message("Module Name : ${ModuleName}")
message("Module Includes : ${Module${ModuleName}_Includes}")
message("Module Sources : ${Module${ModuleName}_Sources}")
message(====================================)